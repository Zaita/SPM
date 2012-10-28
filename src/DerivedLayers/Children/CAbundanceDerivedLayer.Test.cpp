//============================================================================
// Name        : CDerivedLayer.Test.cpp
// Author      : S.Rasmussen
// Date        : 23/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "CAbundanceDerivedLayer.h"
#include "../CDerivedLayerManager.h"
#include "../CDerivedLayer.h"
#include "../../Helpers/CComparer.h"
#include "../../TestFixtures/C1x1_Fixture.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/Ageing.h"
#include "../../TestFixtures/ConfigurationFiles/AgeSize/AgeSize.h"
#include "../../TestFixtures/ConfigurationFiles/SizeWeight/SizeWeight.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/ConstantRecruitment.h"
#include "../../TestFixtures/ConfigurationFiles/Selectivities/Constant.h"
#include "../../TestFixtures/ConfigurationFiles/DerivedLayers/DerivedLayer.h"
#include "../../TestFixtures/ConfigurationFiles/Layers/DoubleLayer.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( Abundance_Derived_Layer, C1x1_Fixture ) {

  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(age_size_vonB);
  addToConfiguration(size_weight_none);
  addToConfiguration(constant_recruitment);
  addToConfiguration(derived_layer);
  addToConfiguration(constant);
  addToConfiguration(numeric);
  addToTimeStep("ageing constant_recruitment");
  loadAndRunEnvironment();

  // Check our Results
  CDerivedLayerManager *pManager     = CDerivedLayerManager::Instance();
  CDerivedLayer        *pLayer    = pManager->getDerivedLayer("derived_layer");
  CWorldSquare            *pSquare      = getSquare();

  // Check Results
  BOOST_CHECK_EQUAL(15, pLayer->getValuesSize());
  BOOST_CHECK_EQUAL(pSquare->getAbundance(), pLayer->getValue(0));
  BOOST_CHECK_EQUAL(pLayer->getValue(1), 1400.0);
  BOOST_CHECK_EQUAL(pLayer->getValue(2), 1300.0);
  BOOST_CHECK_EQUAL(pLayer->getValue(3), 1200.0);
  BOOST_CHECK_EQUAL(pLayer->getValue(4), 1100.0);
  BOOST_CHECK_EQUAL(pLayer->getValue(5), 1000.0);
  BOOST_CHECK_EQUAL(pLayer->getValue(6), 900.0);
  BOOST_CHECK_EQUAL(pLayer->getValue(7), 800.0);
  BOOST_CHECK_EQUAL(pLayer->getValue(8), 700.0);
  BOOST_CHECK_EQUAL(pLayer->getValue(9), 600.0);
  BOOST_CHECK_EQUAL(pLayer->getValue(10), 500.0);
  BOOST_CHECK_EQUAL(pLayer->getValue(11), 400.0);
  BOOST_CHECK_EQUAL(pLayer->getValue(12), 300.0);
  BOOST_CHECK_EQUAL(pLayer->getValue(13), 200.0);
  BOOST_CHECK_EQUAL(pLayer->getValue(14), 100.0);
  BOOST_CHECK_EQUAL(pLayer->getValue(15), 0.0);
  BOOST_CHECK_EQUAL(pLayer->getValue(16), 0.0); // Too Large, should return 0.0
  BOOST_CHECK_EQUAL(pLayer->getValue(17), 0.0); // ""
}

#endif