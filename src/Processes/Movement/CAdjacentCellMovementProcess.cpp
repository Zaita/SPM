//============================================================================
// Name        : CAdjacentCellMovementProcess.cpp
// Author      : S.Rasmussen
// Date        : 4/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CAdjacentCellMovementProcess.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Layers/CLayerManager.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CComparer.h"

//**********************************************************************
// CAdjacentCellMovementProcess::CAdjacentCellMovementProcess()
// Default Constructor
//**********************************************************************
CAdjacentCellMovementProcess::CAdjacentCellMovementProcess() {

  // Default Values
  pLayer = 0;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_LAYER);
  pParameterList->registerAllowed(PARAM_PROPORTION);

}

//**********************************************************************
// void CAdjacentCellMovementProcess::validate()
// validate
//**********************************************************************
void CAdjacentCellMovementProcess::validate() {
  try {
    // Base Validation
    CMovementProcess::validate();

    // Get our Variables
    pParameterList->fillVector(vCategoryNames, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivityNames, PARAM_SELECTIVITIES);

    // Local Validation
    if (getCategoryCount() == 0)
      CError::errorMissing(PARAM_CATEGORIES);
    if (getSelectivityCount() == 0)
      CError::errorMissing(PARAM_SELECTIVITIES);
    if (getCategoryCount() != getSelectivityCount())
      CError::errorListSameSize(PARAM_CATEGORY, PARAM_SELECTIVITY);

    if (getProportion() < 0.0)
      CError::errorLessThan(PARAM_PROPORTION, PARAM_ZERO);
    if (getProportion() > 1.0)
      CError::errorGreaterThan(PARAM_PROPORTION, PARAM_ONE);

  } catch (string &Ex) {
    Ex = "CAdjacentCellMovementProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAdjacentCellMovementProcess::build()
// build
//**********************************************************************
void CAdjacentCellMovementProcess::build() {
  try {
    // Base Building
    CMovementProcess::build();

    // Get selectivities and categories.
    CSelectivityManager::Instance()->fillVector(vSelectivities, vSelectivityNames);
    pWorld->fillCategoryVector(vCategories, vCategoryNames);

    // Get our Layer
    if (sLayer != "")
      pLayer = CLayerManager::Instance()->getNumericLayer(sLayer);

  } catch (string &Ex) {
    Ex = "CAdjacentCellMovementProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAdjacentCellMovementProcess::execute()
// execute
//**********************************************************************
void CAdjacentCellMovementProcess::execute() {
#ifndef OPTIMIZE
  try {
#endif

    // Base Execution
    CMovementProcess::execute();

    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        // Get Current Squares
        pBaseSquare = pWorld->getBaseSquare(i, j);
        pDiff       = pWorld->getDifferenceSquare(i, j);

        if (!pBaseSquare->getEnabled())
          continue;

        //TODO: Need to move individuals from cells that are defined by a categorical layer. Currently this moves all cells
        //      A seconds numeric layer defines the relative proportions to 'diffuse' So, instead of using 0.25 for
        //      each of the up/down/left/right cells, make these proportional to the layer values in the top/bottom/left/right
        //      cells.

        // Loop Through Categories and Ages
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {

            dCurrent = pBaseSquare->getValue( vCategoryIndex[k], l);
            if(CComparer::isZero(dCurrent))
              continue;
            // get up/down/left/right layer values and convert to proportions
            if (pLayer != 0) {
              if ( (i+1) <= pWorld->getHeight() )
                dLayerValueUp = pLayer->getValue(i+1, j);
              else
                dLayerValueUp = 0.0;
              if ( (i-1) >= 0 )
                dLayerValueDown = pLayer->getValue(i-1, j);
              else
                dLayerValueUp = 0.0;
              if ( (j+1) <= pWorld->getWidth() )
                dLayerValueLeft = pLayer->getValue(i, j+1);
              else
                dLayerValueUp = 0.0;
              if ( (j-1) >= 0 )
                dLayerValueRight = pLayer->getValue(i, j-1);
              else
                dLayerValueUp = 0.0;
              dLayerTotal = dLayerValueUp + dLayerValueDown + dLayerValueLeft + dLayerValueRight;
              if(dLayerTotal > 0.0) {
                dLayerValueUp = dLayerValueUp/dLayerTotal * dProportion * vSelectivityIndex[k]->getResult(l);
                dLayerValueDown = dLayerValueDown/dLayerTotal * dProportion * vSelectivityIndex[k]->getResult(l);
                dLayerValueLeft = dLayerValueLeft/dLayerTotal * dProportion * vSelectivityIndex[k]->getResult(l);
                dLayerValueRight = dLayerValueRight/dLayerTotal * dProportion * vSelectivityIndex[k]->getResult(l);
              } else {
                dLayerValueUp = 0.0;
                dLayerValueDown = 0.0;
                dLayerValueLeft = 0.0;
                dLayerValueRight = 0.0;
              }
             // or if no layer defined, then just move 1/4 each way
            } else {
              dLayerValueUp = 0.25 * dProportion * vSelectivityIndex[k]->getResult(l);;
              dLayerValueDown = 0.25 * dProportion * vSelectivityIndex[k]->getResult(l);;
              dLayerValueLeft = 0.25 * dProportion * vSelectivityIndex[k]->getResult(l);;
              dLayerValueRight = 0.25 * dProportion * vSelectivityIndex[k]->getResult(l);;
            }
            // Move
            moveUp(i, j, vCategoryIndex[k], l, dLayerValueUp);
            moveDown(i, j, vCategoryIndex[k], l, dLayerValueDown);
            moveLeft(i, j, vCategoryIndex[k], l, dLayerValueLeft);
            moveRight(i, j, vCategoryIndex[k], l, dLayerValueRight);

          }
        }
      }
    }

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CAdjacentCellMovementProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CAdjacentCellMovementProcess::~CAdjacentCellMovementProcess()
// Default De-Constructor
//**********************************************************************
CAdjacentCellMovementProcess::~CAdjacentCellMovementProcess() {
}
