//============================================================================
// Name        : CDESolver.h
// Author      : S.Rasmussen
// Date        : 1/05/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CDESOLVER_H_
#define CDESOLVER_H_

// Local Headers
#include "../CMinimizer.h"

//**********************************************************************
//
//
//**********************************************************************
class CDESolver : public CMinimizer {
public:
  // Functions
  CDESolver();
  virtual                    ~CDESolver();
  void                       runEstimation();

};

#endif /*CDESOLVER_H_*/