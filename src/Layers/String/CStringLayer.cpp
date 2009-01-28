//============================================================================
// Name        : CStringLayer.cpp
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CStringLayer.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CStringLayer::CStringLayer()
// Default Constructor
//**********************************************************************
CStringLayer::CStringLayer() {
  // Register user allowed variables
  pParameterList->registerAllowed(PARAM_ROW);
}

//**********************************************************************
// string CStringLayer::getValue(int RowIndex, int ColIndex)
// get Value
//**********************************************************************
string CStringLayer::getValue(int RowIndex, int ColIndex) {
  // Vars
  string sRet = "";
#ifndef OPTIMISE
  try {
    // Check
    if (RowIndex >= iHeight)
      CError::errorGreaterThanEqualTo(PARAM_ROW_INDEX, PARAM_LAYER_HEIGHT);
    if (ColIndex >= iWidth)
      CError::errorGreaterThanEqualTo(PARAM_COLUMN_INDEX, PARAM_LAYER_WIDTH);
#endif

    // Assign Ret
    sRet = pGrid[RowIndex][ColIndex];

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CStringLayer.getValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return sRet;
}

//**********************************************************************
// void CStringLayer::Validate()
// Validate
//**********************************************************************
void CStringLayer::validate() {
  try {
    // Base Validate
    CLayer::validate();

    // Build 2D Array
    pGrid = new string*[iHeight];
    for (int i = 0; i < iHeight; ++i) {
      pGrid[i] = new string[iWidth];
    }

    // Fill a new vector with our row information
    vector<string> vData;

    pParameterList->fillVector(vData, PARAM_DATA);

    int iRow  = 0;
    int iCol  = 0;

    for (int i = 0; i < (int)vData.size(); ++i) {
      if (vData[i] == PARAM_DATA)
        continue;

      if (iRow >= iHeight)
        throw string("Too much data"); // TODO: Add CError

      if (iCol >= iWidth) {
        iCol = 0;
        iRow++;
      }

      pGrid[iRow][iCol] = vData[i];
      iCol++;
    }

    if (((iRow+1) != iHeight) || (iCol != iWidth))
      throw string("Not enough data"); // TODO: Add CError

  } catch(string Ex) {
    Ex = "CStringLayer.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CStringLayer::~CStringLayer()
// Default De-Constructor
//**********************************************************************
CStringLayer::~CStringLayer() {
  // Clean Our Grid
  if (pGrid != 0) {
    for (int i = 0; i < iHeight; ++i) {
      delete [] pGrid[i];
      pGrid[i] = 0;
    }

    delete [] pGrid;
  }
}
