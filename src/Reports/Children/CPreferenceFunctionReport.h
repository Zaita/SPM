//============================================================================
// Name        : CPreferenceFunctionReport.h
// Author      : S.Rasmussen
// Date        : 26/03/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPREFERENCEFUNCTIONREPORT_H_
#define CPREFERENCEFUNCTIONREPORT_H_

// Local headers
#include "Base/CFileReport.h"

// Forward-Declaration
class CPreferenceFunction;

//**********************************************************************
//
//
//**********************************************************************
class CPreferenceFunctionReport: public CFileReport {
public:
  CPreferenceFunctionReport();
  virtual                     ~CPreferenceFunctionReport();
  CReport*                    clone() { return new CPreferenceFunctionReport(*this); }
  void                        validate();
  void                        build();
  void                        execute();

protected:
  string                      sPreferenceFunction;
  CPreferenceFunction         *pPreferenceFunction;
};

#endif /* CPREFERENCEFUNCTIONREPORT_H_ */