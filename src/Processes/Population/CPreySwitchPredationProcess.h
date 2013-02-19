//============================================================================
// Name        : CPreySwitchPredationProcess.h
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPRESWITCHPREDATIONPROCESS_H_
#define CPRESWITCHPREDATIONPROCESS_H_

// Local headers
#include "../CProcess.h"

// Forward-Dec
class CPenalty;
class CTimeStepManager;

//**********************************************************************
//
//
//**********************************************************************
class CPreySwitchPredationProcess : public CProcess {
public:
  // Functions
  CPreySwitchPredationProcess();
  virtual                     ~CPreySwitchPredationProcess();
  CProcess*                   clone() { return new CPreySwitchPredationProcess(*this); }
  void                        validate();
  void                        build();
  void                        rebuild();
  void                        execute();
  vector<int>                 getMortalityYears() { return vMortalityYears; }
  vector<double>              getMortalityRate() { return vMortalityRate; }
  vector<double>              getMortalityN() { return vMortalityN; }
  vector<double>              getMortalityBiomass() { return vMortalityBiomass; }
  vector<double>              getPredatorBiomass() { return vPredatorBiomass; }
  bool                        isAbundance() { return bIsAbundance; }
  int                         getPredatorCategoryCount() { return vPredatorCategoryList.size(); }
  int                         getPredatorSelectivityCount() { return vPredatorSelectivityList.size(); }

protected:
  // Variables
  CWorldSquare                **pGrid;
  CWorldSquare                *pWorldSquare;
  bool                        bIsAbundance;
  double                      dA;
  double                      dB;
  double                      dX;
  double                      dUMax;
  double                      dMortality;
  double                      dExploitation;
  double                      dVulnerable;
  double                      dPredatorVulnerable;
  vector<string>              vPredatorCategoryList;
  vector<int>                 vPredatorCategoryIndex;
  vector<string>              vPredatorSelectivityList;
  vector<CSelectivity*>       vPredatorSelectivityIndex;
  double                      dPredatorCurrent;
  vector<int>                 vMortalityYears;
  vector<double>              vMortalityRate;
  vector<double>              vMortalityN;
  vector<double>              vMortalityBiomass;
  vector<double>              vPredatorBiomass;
  string                      sPenalty;
  CPenalty                    *pPenalty;
  CTimeStepManager            *pTimeStepManager;

};

#endif /* CPRESWITCHPREDATIONPROCESS_H_ */
