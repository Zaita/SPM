//============================================================================
// Name        : CGumbelPreferenceFunction.cpp
// Author      : C. Marsh
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================

// Local Headers
#include "CGumbelPreferenceFunction.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/DefinedValues.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../PDFs/CPDF.h"
#include "../../PDFs/CPDFManager.h"

//**********************************************************************
// CGumbelPreferenceFunction::CGumbelPreferenceFunction()
// Default Constructor
//**********************************************************************
CGumbelPreferenceFunction::CGumbelPreferenceFunction() {

  // Register Estimables
  registerEstimable(PARAM_RHO, &dRho);

  // Register user allowed variables
  pParameterList->registerAllowed(PARAM_RHO);
  pParameterList->registerAllowed(PARAM_PDFS);
  pParameterList->registerAllowed(PARAM_LAYERS);

}

//**********************************************************************
// void CGumbelPreferenceFunction::validate()
// Validate
//**********************************************************************
void CGumbelPreferenceFunction::validate() {
  try {

    // Assign our variables
    dRho  = pParameterList->getDouble(PARAM_RHO);
    pParameterList->fillVector(vPDFNames, PARAM_PDFS);
    pParameterList->fillVector(vLayerNames, PARAM_LAYERS);

    // Validate parent
    CPreferenceFunction::validate();

    //********************************************
    //  We allow only two PDF's
    //*********************************************
    //Ensure exactly 2 PDFs
    if (vPDFNames.size() != 2)
      CError::errorNotEqual(PARAM_PDFS, "two");

    //Ensure exactly 2 layers
    if (vLayerNames.size() != 2)
      CError::errorNotEqual(PARAM_LAYERS, "two");

  } catch (string &Ex) {
    Ex = "CGumbelPreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CGumbelPreferenceFunction::build()
// Validate
//**********************************************************************
void CGumbelPreferenceFunction::build() {

  // Build parent
  CPreferenceFunction::build();

  // Get PDFs
  CPDFManager *pPDFManager = CPDFManager::Instance();

  for (int i=0; i< (int)vPDFNames.size(); ++i) {
    vPDFs.push_back( pPDFManager->getPDF(vPDFNames[i]) );
    vPDFTypes.push_back(vPDFs[i]->getPDFType());
  }

  // Get Layers
  CLayerManager *pLayerManager = CLayerManager::Instance();

  for (int i=0; i< (int)vLayerNames.size(); ++i) {
    vLayers.push_back( pLayerManager->getNumericLayer(vLayerNames[i]) );
  }
}

//**********************************************************************
// double CGumbelPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// get Result
//**********************************************************************
double CGumbelPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {

  dRet = 0.0;

#ifndef OPTIMIZE
  try {
#endif

    vector<double> dValue;

    double x1 = vLayers[0]->getValue(TRIndex, TCIndex, RIndex, CIndex);
    double x2 = vLayers[1]->getValue(TRIndex, TCIndex, RIndex, CIndex);

    // Evaluate using Frank copula
    double dPDF1 = vPDFs[0]->getPDFResult(x1);
    double dPDF2 = vPDFs[1]->getPDFResult(x2);

    double dCDF1 = vPDFs[0]->getCDFResult(x1);
    double dCDF2 = vPDFs[1]->getCDFResult(x2);

    dRet = exp(- pow(-log(dCDF1),dRho));// blah blah .. * dPDF1 * dPDF2;

    //dRet = exp(- ((-log(dCDF1))^dRho + (-log(dCDF2))^dRho)^(1/dRho) * (((-log(dCDF1))^(dRho-1))/dCDF1) * (((-log(dCDF2))^(dRho-1))/dCDF2) *
    //       (((-log(dCDF1))^dRho + (-log(dCDF2))^dRho)^((2/dRho)-2) + ((dRho-1) * ((-log(dCDF1))^dRho + (-log(dCDF2))^Theta)^((1/(dRho)-2)))))* dPDF1 * dPDF2;

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CGumbelPreferenceFunction.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return CMath::zeroFun(pow(dRet,dAlpha),ZERO);
}
//**********************************************************************
// CGumbelPreferenceFunction::~CGumbelPreferenceFunction()
// Default De-Constructor
//**********************************************************************
CGumbelPreferenceFunction::~CGumbelPreferenceFunction() {
}