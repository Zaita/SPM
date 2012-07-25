//============================================================================
// Name        : CEstimate.cpp
// Author      : S.Rasmussen
// Date        : 27/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Headers
#include <boost/lexical_cast.hpp>

#include "CEstimate.h"
#include "../Priors/CPriorManager.h"
#include "../Priors/CPrior.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"
#include "../Helpers/CConvertor.h"
#include "../ObjectFinder/CObjectFinder.h"

//**********************************************************************
// CEstimate::CEstimate()
// Default Constructor
//**********************************************************************
CEstimate::CEstimate() {
  // Default Values
  pPrior    = 0;
  pTarget   = 0;
  bEnabled  = true;
}

//**********************************************************************
// void CEstimate::addValue(double value)
// Add A Value to our Estimate
//**********************************************************************
void CEstimate::addValue(double value) {
  vValueList.push_back(value);
}


//**********************************************************************
// void CEstimateInfo::fillSameVector(vector<string> &sames)
// Fill a Vector with our "Same" parameters
//**********************************************************************
void CEstimate::fillSameVector(vector<string> &sames) {
  sames.assign(vSameList.begin(), vSameList.end());
}

//**********************************************************************
// void CEstimate::setValue(double value)
// Set Value of our Target
//**********************************************************************
void CEstimate::setValue(double value) {
#ifndef OPTIMIZE
  try {
#endif
    if (pTarget == 0)
      throw string(ERROR_INVALID_TARGET_NULL);

    (*pTarget) = value;

    // Set our Sames.
    foreach(double* Target, vSameIndex) {
      (*Target) = value;
    }

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CEstimate.setValue()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// double CEstimate::getValue()
// Get the Value of our Target
//**********************************************************************
double CEstimate::getValue() {
#ifndef OPTIMIZE
  try {
    if (pTarget == 0)
      throw string(ERROR_INVALID_TARGET_NULL);

  } catch (string &Ex) {
    Ex = "CEstimate.getValue()->" + Ex;
    throw Ex;
  }
#endif
  return (*pTarget);
}

//**********************************************************************
// double CEstimate::getPriorScore()
// Get The Score for Our Prior
//**********************************************************************
double CEstimate::getPriorScore() {
#ifndef OPTIMIZE
  try {
    if (pPrior == 0)
          CError::errorMissing(PARAM_PRIOR);
#endif

    if (sPrior == "")
      return 0.0; // No Prior

    return pPrior->getResult((*pTarget));

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CEstimate.getPriorScore(" + getParameter() + ")->" + Ex;
    throw Ex;
  }
  return 0.0;
#endif
}

//**********************************************************************
// void CEstimate::loadValue(int index)
// Load Our Value
//**********************************************************************
void CEstimate::loadValue(int index) {
  try {
    if (index < 0)
      throw string(ERROR_INVALID_IDX + boost::lexical_cast<string>(index));
    if (index >= (int)vValueList.size())
      throw string(ERROR_INVALID_IDX + boost::lexical_cast<string>(index));

    setValue(vValueList[index]);

  } catch (string &Ex) {
    Ex = "CEstimate.loadValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}



//**********************************************************************
// void CEstimate::validate()
// validate
//**********************************************************************
void CEstimate::validate() {
  try {
    // Base
    CBaseBuild::validate();

    // Populate our Variables
    sParameter        = pParameterList->getString(PARAM_PARAMETER);
    dLowerBound       = pParameterList->getDouble(PARAM_LOWER_BOUND);
    dUpperBound       = pParameterList->getDouble(PARAM_UPPER_BOUND);
    bMCMCFixed        = pParameterList->getBool(PARAM_MCMC_FIXED,true,false);
    sPrior            = pParameterList->getString(PARAM_PRIOR, true, "");
    iEstimationPhase  = pParameterList->getInt(PARAM_ESTIMATION_PHASE, true, 1);

    pParameterList->fillVector(vSameList, PARAM_SAME, true);

    // Validate
    if (dUpperBound < dLowerBound)
      CError::errorLessThan(PARAM_UPPER_BOUND, PARAM_LOWER_BOUND);

    // Check For Duplicate Sames
    map<string, int>  mSames;
    foreach(string Same, vSameList) {
      mSames[Same]++;
      if (mSames[Same] > 1)
        CError::errorDuplicate(PARAM_SAME, Same);
    }

  } catch (string &Ex) {
    Ex = "CEstimate.validate(" + sParameter + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimate::build()
// build
//**********************************************************************
void CEstimate::build() {
  try {
    // Build our Prior Target
    if (sPrior != "") {
      CPriorManager *pPriorManager = CPriorManager::Instance();
      pPrior = pPriorManager->getPrior(sPrior);
    }

    // Populate Same Index
    vSameIndex.clear();
    foreach(string Same, vSameList) {
      double *target = CObjectFinder::getObjectEstimable(Same);
      vSameIndex.push_back(target);
    }

  } catch (string &Ex) {
    Ex = "CEstimate.build(" + sParameter + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CEstimate::~CEstimate()
// Default De-Constructor
//**********************************************************************
CEstimate::~CEstimate() {
}
