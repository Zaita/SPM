//============================================================================
// Name        : CProportionsAtAgeObservation.cpp
// Author      : S.Rasmussen
// Date        : 17/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Global Headers
#include <iostream>

// Local Headers
#include "CProportionsAtAgeObservation.h"
#include "../../Layers/String/CStringLayer.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/CComparer.h"
#include "../../AgeingError/CAgeingErrorManager.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
// CProportionsAtAgeObservation::CProportionsAtAgeObservation()
// Default Constructor
//**********************************************************************
CProportionsAtAgeObservation::CProportionsAtAgeObservation() {

  // Default Values
  pAgeResults         = 0;
  iMinAge             = -1;
  iMaxAge             = -1;
  bAgePlus            = false;
  bRescale            = false;
  pAgeingError        = 0;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_MIN_AGE);
  pParameterList->registerAllowed(PARAM_MAX_AGE);
  pParameterList->registerAllowed(PARAM_AGE_PLUS_GROUP);
  pParameterList->registerAllowed(PARAM_TOLERANCE);
  pParameterList->registerAllowed(PARAM_OBS);
  pParameterList->registerAllowed(PARAM_DELTA);
  pParameterList->registerAllowed(PARAM_ERROR_VALUE);
  pParameterList->registerAllowed(PARAM_PROPORTION_TIME_STEP);
  pParameterList->registerAllowed(PARAM_PROCESS_ERROR);
  pParameterList->registerAllowed(PARAM_AGEING_ERROR);
}

//**********************************************************************
// void CProportionsAtAgeObservation::Validate()
// Validate
//**********************************************************************
void CProportionsAtAgeObservation::validate() {
  try {
    // Base
    CObservation::validate();

    // Populate our Parameters
    iMinAge             = pParameterList->getInt(PARAM_MIN_AGE);
    iMaxAge             = pParameterList->getInt(PARAM_MAX_AGE);
    bAgePlus            = pParameterList->getBool(PARAM_AGE_PLUS_GROUP,true,true);
    dDelta              = pParameterList->getDouble(PARAM_DELTA,true,DELTA);
    dTolerance          = pParameterList->getDouble(PARAM_TOLERANCE,true,0.001);
    dProportionTimeStep = pParameterList->getDouble(PARAM_PROPORTION_TIME_STEP,true,1.0);
    dProcessError       = pParameterList->getDouble(PARAM_PROCESS_ERROR,true,0);
    sAgeingError        = pParameterList->getString(PARAM_AGEING_ERROR, true, PARAM_NONE);

    if (iMinAge < pWorld->getMinAge())
      CError::errorLessThan(PARAM_MIN_AGE, PARAM_MIN_AGE);
    if (iMaxAge > pWorld->getMaxAge())
      CError::errorGreaterThan(PARAM_MAX_AGE, PARAM_MAX_AGE);
    if (dProcessError < 0)
      CError::errorLessThan(PARAM_PROCESS_ERROR, PARAM_ZERO);

    // Find out the Spread in Ages
    int iAgeSpread = (iMaxAge+1) - iMinAge;

    // Get our OBS
    vector<string> vOBS;
    pParameterList->fillVector(vOBS, PARAM_OBS);

    if ((vOBS.size() % (iAgeSpread+1)) != 0)
      throw string("OBS not right amount"); //TODO: better error message

    for (int i = 0; i < (int)vOBS.size(); i+=(iAgeSpread+1)) {
      for (int j = 0; j < iAgeSpread; ++j) {
        mvProportionMatrix[vOBS[i]].push_back(CConvertor::stringToDouble(vOBS[i+j+1]));
      }
    }

    // Get our Error Value
    vector<string> vErrorValues;
    pParameterList->fillVector(vErrorValues, PARAM_ERROR_VALUE);

    if ((vErrorValues.size() % 2) != 0)
      throw string(PARAM_ERROR_VALUE + string(ERROR_NOT_CONTAIN_EVEN_ELEMENTS));

    for (int i = 0; i < (int)vErrorValues.size(); i+=2) {
      mErrorValue[vErrorValues[i]] = CConvertor::stringToDouble(vErrorValues[i+1]);
      // Check for negative values
      if(mErrorValue[vErrorValues[i]] < 0.0)
        CError::errorLessThan(PARAM_ERROR_VALUE, PARAM_ZERO);
    }

    // TODO: Make mErrorValue a map of vectors and replicate the N's to the same length
    // as OBS. One of the likelihoods requires a vector while the other doesn't.

    // Loop Through our Partitions
    map<string, vector<double> >::iterator vPropPtr = mvProportionMatrix.begin();
    while (vPropPtr != mvProportionMatrix.end()) {
      // Validate Sizes
      if (iAgeSpread > (int)((*vPropPtr).second).size())
        throw string(ERROR_QTY_LESS_PROPORTIONS + (*vPropPtr).first);
      if (iAgeSpread < (int)((*vPropPtr).second).size())
        throw string(ERROR_QTY_MORE_PROPORTIONS + (*vPropPtr).first);

        // Rescale if Tolerance is exceeded
        double dRunningTotal = 0.0;
        vector<double>::iterator vPtr3 = ((*vPropPtr).second).begin();
        while (vPtr3 != ((*vPropPtr).second).end()) {
          dRunningTotal += (*vPtr3);
          vPtr3++;
        }

        if (fabs(1.0-dRunningTotal) > dTolerance) {
          vector<double>::iterator vPtr4 = ((*vPropPtr).second).begin();
          while (vPtr4 != ((*vPropPtr).second).end()) {
            (*vPtr4) /= dRunningTotal;
            vPtr4++;
          }
        }
      vPropPtr++;
    }
    // Must be same size
    if (vCategoryNames.size() != vSelectivityNames.size())
      CError::errorListSameSize(PARAM_CATEGORY, PARAM_SELECTIVITY);

    // Number of N's must be equal to number of Proportions
    if (mErrorValue.size() != mvProportionMatrix.size())
      CError::errorListSameSize(PARAM_N, PARAM_OBS);

    // Validate our N's against the OBS
    // They have to have a 1-to-1 relationship
    bool bMatch = false;
    map<string, double>::iterator vNPtr = mErrorValue.begin();

    while (vNPtr != mErrorValue.end()) {
      bMatch = false;
      // Loop Props Looking For Match;
      vPropPtr = mvProportionMatrix.begin();
      while (vPropPtr != mvProportionMatrix.end()) {
        if ((*vPropPtr).first == (*vNPtr).first) {
          bMatch = true;
          break;
          }
      vPropPtr++;
      }

      if (!bMatch)
        throw string(ERROR_MISSING_N_OBS + (*vNPtr).first);

      vNPtr++;
    }
  } catch (string Ex) {
    Ex = "CProportionsAtAgeObservation.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProportionsAtAgeObservation::build()
// Build
//**********************************************************************
void CProportionsAtAgeObservation::build() {
  try {
    // Base Build
    CObservation::build();

    // Ageing Error
    pAgeingError = CAgeingErrorManager::Instance()->getAgeingError(sAgeingError);

    // Create Array of Age Results
    iArraySize = (iMaxAge+1) - iMinAge;

    if (pAgeResults == 0)
      pAgeResults = new double[iArraySize];
    for (int i = 0; i < iArraySize; ++i)
      pAgeResults[i] = 0.0;

  } catch (string Ex) {
    Ex = "CProportionsAtAgeObservation.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProportionsAtAgeObservation::execute()
// Execute
//**********************************************************************
void CProportionsAtAgeObservation::execute() {
#ifndef OPTIMIZE
  try {
#endif
    // Variables
    int                 iSquareAgeOffset   = iMinAge - pWorld->getMinAge();
                        dScore             = 0.0;
    double              dRunningTotal      = 0.0;
    double              dCurrentProp       = 0.0;
    vector<string>      vKeys;
    vector<double>      vExpected;
    vector<double>      vObserved;
    vector<double>      vProcessError;
    vector<double>      vErrorValue;
    vector<double>      vScores;

    // Base
    CObservation::execute();

    pWorldView->execute();

    // Loop Through Observations
    map<string, vector<double> >::iterator mvPropPtr = mvProportionMatrix.begin();
    while (mvPropPtr != mvProportionMatrix.end()) {
      // Get Square for this Area
      pBaseSquare = pWorldView->getSquare((*mvPropPtr).first);

      // Loop Through Ages in that square and add them to count
      for (int i = 0; i < iArraySize; ++i) {
        // Loop Through Categories
        for (int j = 0; j < (int)vCategories.size(); ++j) {
          double dSelectResult = vSelectivities[j]->getResult((i+iSquareAgeOffset));
          pAgeResults[i] += dSelectResult * pBaseSquare->getPopulationInCategoryForAge((i+iSquareAgeOffset), vCategories[j]);
        }
      }

      // And if the observation has a plus group
      if(bAgePlus) {
        // Loop Through Plus Group Ages in that square and add them to count for the Plus group
        for (int i = iArraySize+iSquareAgeOffset; i < pWorld->getAgeSpread(); ++i) {
          // Loop Through Categories
          for (int j = 0; j < (int)vCategories.size(); ++j) {
            double dSelectResult = vSelectivities[j]->getResult(i);
            pAgeResults[iArraySize-1] += dSelectResult * pBaseSquare->getPopulationInCategoryForAge(i, vCategories[j]);
          }
        }
      }

      // Populate our Running Total
      dRunningTotal = 0.0;

      for (int i = 0; i < iArraySize; ++i)
        dRunningTotal += pAgeResults[i];

      for (int i = 0; i < iArraySize; ++i) {
        // Get our Proportion
        if(!CComparer::isZero(dRunningTotal))
          dCurrentProp = pAgeResults[i] / dRunningTotal;
        else
          dCurrentProp = 0.0;

        // Store the items we want to calculate scores for
        vKeys.push_back((*mvPropPtr).first);
        vExpected.push_back(dCurrentProp);
        vObserved.push_back(((*mvPropPtr).second)[i]);
        vProcessError.push_back(dProcessError);
        vErrorValue.push_back(mErrorValue[(*mvPropPtr).first]);
      }

      // Clear Our Age Results
      for (int i = 0; i < iArraySize; ++i)
        pAgeResults[i] = 0.0;

      mvPropPtr++;
    }

    // Simulate or Generate Result?
    if (pRuntimeController->getRunMode() == RUN_MODE_SIMULATION) {
      // Simulate our values, then save them
      pLikelihood->simulateObserved(vKeys, vObserved, vExpected, vErrorValue, vProcessError, dDelta);
      for (int i = 0; i < (int)vObserved.size(); ++i)
        saveComparison(vKeys[i], vExpected[i], vObserved[i], vErrorValue[i], 0.0);

    } else { // Generate Score
      dScore = pLikelihood->getInitialScore(vKeys, vProcessError, vErrorValue);

      // Generate Results and save them
      pLikelihood->getResult(vScores, vExpected, vObserved, vErrorValue, vProcessError, dDelta);
      for (int i = 0; i < (int)vScores.size(); ++i) {
        dScore += vScores[i];
        saveComparison(vKeys[i], vExpected[i], vObserved[i], pLikelihood->adjustErrorValue(vProcessError[i], vErrorValue[i]), vScores[i]);
      }
    }

#ifndef OPTIMIZE
  } catch (string Ex) {
    Ex = "CProportionsAtAgeObservation.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CProportionsAtAgeObservation::~CProportionsAtAgeObservation()
// Default De-Constructor
//**********************************************************************
CProportionsAtAgeObservation::~CProportionsAtAgeObservation() {
  // Clear Age Results
  if (pAgeResults != 0)
    delete [] pAgeResults;
}
