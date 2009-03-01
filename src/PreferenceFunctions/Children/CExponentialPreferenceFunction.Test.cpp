//============================================================================
// Name        : CExponentialPreferenceFunction.Test.cpp
// Author      : S.Rasmussen
// Date        : 19/02/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../Factory/CPreferenceFunctionFactory.h"
#include "../../TestFixtures/CLayer_Fixture.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( ExponentialPreferenceFunction_DoubleLayer, CLayer_Fixture ) {

  CPreferenceFunction *pPreference = 0;
  BOOST_REQUIRE_NO_THROW(pPreference = CPreferenceFunctionFactory::buildPreferenceFunction(PARAM_EXPONENTIAL, false));

  pPreference->addParameter(PARAM_LABEL, "exponential");
  pPreference->addParameter(PARAM_ALPHA, "3");
  pPreference->addParameter(PARAM_LAMBDA, "4.0");
  pPreference->addParameter(PARAM_LAYER, "double_layer");

  BOOST_REQUIRE_NO_THROW(pPreference->validate());
  BOOST_REQUIRE_NO_THROW(pPreference->build());

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 0), 6.1442123533282081e-006);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 1), 6.1633793064669094e-011);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 2), 5.0000057988138013e-011);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 3), 5.000000000035629e-011);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 4), 5.0000000000000002e-011);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 0), 5.0000000000000002e-011);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 1), 5.0000000000000002e-011);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 2), 5.0000000000000002e-011);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 3), 5.0000000000000002e-011);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 4), 5.0000000000000002e-011);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 0), 6.1442123533282081e-006);
  BOOST_CHECK_EQUAL(pPreference->getResult(1, 0, 0, 1), 6.1633793064669094e-011);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 2, 0, 2), 5.0000057988138013e-011);
  BOOST_CHECK_EQUAL(pPreference->getResult(3, 0, 0, 3), 5.000000000035629e-011);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 4, 0, 4), 5.0000000000000002e-011);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 0), 5.0000000000000002e-011);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 1, 3, 1), 5.0000000000000002e-011);
  BOOST_CHECK_EQUAL(pPreference->getResult(2, 0, 3, 2), 5.0000000000000002e-011);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 3, 3, 3), 5.0000000000000002e-011);
  BOOST_CHECK_EQUAL(pPreference->getResult(4, 0, 3, 4), 5.0000000000000002e-011);

  delete pPreference;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( ExponentialPreferenceFunction_DistanceLayer, CLayer_Fixture ) {

  CPreferenceFunction *pPreference = 0;
  BOOST_REQUIRE_NO_THROW(pPreference = CPreferenceFunctionFactory::buildPreferenceFunction(PARAM_EXPONENTIAL, false));

  pPreference->addParameter(PARAM_LABEL, "exponential");
  pPreference->addParameter(PARAM_ALPHA, "2");
  pPreference->addParameter(PARAM_LAMBDA, "1.125");
  pPreference->addParameter(PARAM_LAYER, "distance_layer");

  BOOST_REQUIRE_NO_THROW(pPreference->validate());
  BOOST_REQUIRE_NO_THROW(pPreference->build());

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 0), 1.0);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 1), 0.10539922456186435);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 2), 0.011108996538242306);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 3), 0.0011708796207911742);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 4), 0.00012340980408667953);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 0), 0.0011708796207911742);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 1), 0.00081271933015818405);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 2), 0.00029977140119418876);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 3), 7.1490817290299329e-005);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 4), 1.300729765406762e-005);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 0, 0), 1.0);
  BOOST_CHECK_EQUAL(pPreference->getResult(1, 0, 0, 1), 0.04150337559812748);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 2, 0, 2), 1.0);
  BOOST_CHECK_EQUAL(pPreference->getResult(3, 0, 0, 3), 7.1490817290299329e-005);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 4, 0, 4), 1.0);

  BOOST_CHECK_EQUAL(pPreference->getResult(0, 0, 3, 0), 0.0011708796207911742);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 1, 3, 1), 0.0011708796207911742);
  BOOST_CHECK_EQUAL(pPreference->getResult(2, 0, 3, 2), 0.0065312759973169838);
  BOOST_CHECK_EQUAL(pPreference->getResult(0, 3, 3, 3), 0.0011708796207911742);
  BOOST_CHECK_EQUAL(pPreference->getResult(4, 0, 3, 4), 9.3552511627110688e-005);

  delete pPreference;
}

#endif
