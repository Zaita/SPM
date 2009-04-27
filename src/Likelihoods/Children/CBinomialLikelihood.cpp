//============================================================================
// Name        : CBinomialLikelihood.cpp
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <cmath>

// Local headers
#include "CBinomialLikelihood.h"
#include "../../Helpers/CMath.h"

//**********************************************************************
// CBinomialLikelihood::CBinomialLikelihood()
// Default Constructor
//**********************************************************************
CBinomialLikelihood::CBinomialLikelihood() {
}

//**********************************************************************
// double CBinomialLikelihood::adjustErrorValue(double processError, double errorValue)
// Adjust our ErrorValue based on process error
//**********************************************************************
double CBinomialLikelihood::adjustErrorValue(double processError, double errorValue) {
  // adjust for N process error
  if(errorValue > 0 && processError > 0)
    return (1.0/(1.0/errorValue + 1.0/processError));

<<<<<<< .mine  if ( (processError >= 0.0) && (errorValue > 0.0) )
    return (1.0 / (1.0 / errorValue + 1.0 / errorValue));

=======>>>>>>> .theirs  return errorValue;
}

//**********************************************************************
// double CBinomialLikelihood::getResult(double expected, double observed, double errorValue, double processError, double delta)
// Calculate the Result of this Likelihood
//**********************************************************************
double CBinomialLikelihood::getResult(double expected, double observed, double errorValue, double processError,
    double delta) {

  errorValue = adjustErrorValue(processError, errorValue);

  double dTemp = CMath::lnFactorial(errorValue) - CMath::lnFactorial(errorValue * (1 - observed)) - CMath::lnFactorial(
      errorValue * observed) + errorValue * observed * log(CMath::zeroFun(expected, delta)) + errorValue * (1
          - observed) * log(CMath::zeroFun(1 - expected, delta));

  return dTemp;
}

//**********************************************************************
// double CBinomialLikelihood::simulateObserved(double expected, double errorValue, double processError, double delta)
//
//**********************************************************************
double CBinomialLikelihood::simulateObserved(double expected, double errorValue, double processError, double delta) {
  throw string("CBinomialLikelihood.simulateObserved() not yet implemented");
}

//**********************************************************************
// CBinomialLikelihood::~CBinomialLikelihood()
// Destructor
//**********************************************************************
CBinomialLikelihood::~CBinomialLikelihood() {
}
