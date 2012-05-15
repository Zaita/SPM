//============================================================================
// Name        : CProportionsAtAgeObservation.Test.cpp
// Author      : S.Rasmussen
// Date        : 28/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../../Observations/CObservation.h"
#include "../../Observations/CObservationManager.h"
#include "../../Helpers/CComparer.h"
#include "../../TestFixtures/C3x3_Fixture.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/Ageing.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/ConstantRecruitment.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/AnnualMortalityRate.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/CategoryTransitionRate.h"
#include "../../TestFixtures/ConfigurationFiles/Selectivities/LogisticProducing.h"
#include "../../TestFixtures/ConfigurationFiles/Selectivities/Constant.h"
#include "../../TestFixtures/ConfigurationFiles/Catchabilities/Catchability.h"
#include "../../TestFixtures/ConfigurationFiles/Layers/StringLayer.h"
#include "../../TestFixtures/ConfigurationFiles/Observations/ProportionsAtAge.h"
#include "../../TestFixtures/ConfigurationFiles/AgeingError/AgeingError.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( ProportionsAtAgeObservation, C3x3_Fixture ) {

  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(constant_recruitment_all_ages);
  addToConfiguration(annual_mortality_rate);
  addToConfiguration(category_transition_rate);
  addToConfiguration(logistic_producing);
  addToConfiguration(catchability_basic);
  addToConfiguration(string_layer);
  addToConfiguration(proportions_at_age_observation);
  addToConfiguration(constant);
  addToTimeStep("ageing constant_recruitment_all_ages category_transition_rate annual_mortality_rate");
  BOOST_REQUIRE_NO_THROW(loadAndRunEnvironment());

  // Check our Results
  CObservationManager *pManager       = CObservationManager::Instance();
  CObservation        *pObservation   = pManager->getObservation("proportions_at_age_observation");

  vector<SComparison*> vComparisons;
  pObservation->fillComparisons(vComparisons);

  BOOST_REQUIRE_EQUAL(vComparisons.size(), 18.0);

  SComparison *pComparison = vComparisons[0];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1000, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.1, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.1051165134496773, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 589.00796476882101, 1e-9);

  pComparison = vComparisons[1];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1000, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.2, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.10504856751026879, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 1313.8984848025439, 1e-9);

  pComparison = vComparisons[2];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1000, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.7, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.78983491904005387, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 4055.1027552970522, 1e-9);

  pComparison = vComparisons[3];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaB");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1200, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.20, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.10511651344967737, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 1619.6575609306892, 1e-9);

  pComparison = vComparisons[4];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaB");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1200, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.30, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.10504856751026881, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 2574.0593690505639, 1e-9);

  pComparison = vComparisons[5];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaB");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1200, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.5, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.78983491904005387, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 3383.8341265379695, 1e-9);

  pComparison = vComparisons[6];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaC");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1300, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.30, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.10511651344967737, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 2819.2469517676313, 1e-9);

  pComparison = vComparisons[7];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaC");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1300, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.40, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.10504856751026881, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 3907.7698890007914, 1e-9);

  pComparison = vComparisons[8];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaC");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1300, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.30, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.78983491904005387, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 2032.7126680893093, 1e-9);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      CWorldSquare *pSquare = getSquare(i,j);

      BOOST_CHECK_CLOSE(pSquare->getAbundance(), 15012.33061011306, 1e-9);

      // Our Expected Results
      double immature[] = { 1111.1111111111111, 1111.1111111111111, 1111.1111111111111, 1111.1111111111111, 1083.3333333333333, 1041.6266318250709, 952.85900493878341, 803.91670313042891, 621.10466653061906, 1404.1008649763676 };
      double mature[] = { 0.0, 0.0, 0.0, 0.0, 27.5260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531, 68.514671490004474, 153.01395904028104, 288.4780206714787, 442.52416779189696, 3680.8881270055226 };
      double spawning[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

      // Check Expected against model
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 0), immature[0], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 1), immature[1], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 2), immature[2], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 3), immature[3], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 4), immature[4], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 5), immature[5], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 6), immature[6], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 7), immature[7], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 8), immature[8], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 9), immature[9], 1e-9);

      BOOST_CHECK_CLOSE(pSquare->getValue(1, 0), mature[0], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 1), mature[1], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 2), mature[2], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 3), mature[3], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 4), mature[4], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 5), mature[5], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 6), mature[6], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 7), mature[7], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 8), mature[8], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 9), mature[9], 1e-9);

      BOOST_CHECK_CLOSE(pSquare->getValue(2, 0), spawning[0], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 1), spawning[1], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 2), spawning[2], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 3), spawning[3], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 4), spawning[4], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 5), spawning[5], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 6), spawning[6], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 7), spawning[7], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 8), spawning[8], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 9), spawning[9], 1e-9);
    }
  }
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( ProportionsAtAgeObservationWithNormalAgeingError, C3x3_Fixture ) {

  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(constant_recruitment_all_ages);
  addToConfiguration(annual_mortality_rate);
  addToConfiguration(category_transition_rate);
  addToConfiguration(logistic_producing);
  addToConfiguration(catchability_basic);
  addToConfiguration(string_layer);
  addToConfiguration(proportions_at_age_observation_with_normal);
  addToConfiguration(constant);
  addToConfiguration(ageingerror_normal);
  addToTimeStep("ageing constant_recruitment_all_ages category_transition_rate annual_mortality_rate");
  BOOST_REQUIRE_NO_THROW(loadAndRunEnvironment());

  // Check our Results
  CObservationManager *pManager       = CObservationManager::Instance();
  CObservation        *pObservation   = pManager->getObservation("proportions_at_age_observation_with_normal");

  vector<SComparison*> vComparisons;
  pObservation->fillComparisons(vComparisons);

  BOOST_REQUIRE_EQUAL(vComparisons.size(), 18.0);

  SComparison *pComparison = vComparisons[0];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1000, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.1, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.10588370214904039, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 588.2807692273251, 1e-9);

  pComparison = vComparisons[1];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1000, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.2, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.10635410777654149, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 1311.4282097942578, 1e-9);

  pComparison = vComparisons[2];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1000, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.7, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.78776219007441806, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 4056.9421490211157, 1e-9);

  pComparison = vComparisons[3];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaB");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1200, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.20, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.10588370214904036, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 1617.9122916310989, 1e-9);

  pComparison = vComparisons[4];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaB");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1200, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.30, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.10635410777654149, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 2569.6128740356489, 1e-9);

  pComparison = vComparisons[5];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaB");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1200, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.5, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.78776219007441806, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 3385.4107497300242, 1e-9);

  pComparison = vComparisons[6];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaC");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1300, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.30, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.10588370214904036, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 2816.4108891557971, 1e-9);

  pComparison = vComparisons[7];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaC");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1300, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.40, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.10635410777654149, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 3901.3471739792476, 1e-9);

  pComparison = vComparisons[8];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaC");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1300, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.30, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.78776219007441806, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 2033.7374731641448, 1e-9);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      CWorldSquare *pSquare = getSquare(i,j);

      BOOST_CHECK_CLOSE(pSquare->getAbundance(), 15012.33061011306, 1e-9);

      // Our Expected Results
      double immature[] = { 1111.1111111111111, 1111.1111111111111, 1111.1111111111111, 1111.1111111111111, 1083.3333333333333, 1041.6266318250709, 952.85900493878341, 803.91670313042891, 621.10466653061906, 1404.1008649763676 };
      double mature[] = { 0.0, 0.0, 0.0, 0.0, 27.5260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531, 68.514671490004474, 153.01395904028104, 288.4780206714787, 442.52416779189696, 3680.8881270055226 };
      double spawning[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

      // Check Expected against model
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 0), immature[0], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 1), immature[1], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 2), immature[2], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 3), immature[3], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 4), immature[4], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 5), immature[5], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 6), immature[6], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 7), immature[7], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 8), immature[8], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 9), immature[9], 1e-9);

      BOOST_CHECK_CLOSE(pSquare->getValue(1, 0), mature[0], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 1), mature[1], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 2), mature[2], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 3), mature[3], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 4), mature[4], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 5), mature[5], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 6), mature[6], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 7), mature[7], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 8), mature[8], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 9), mature[9], 1e-9);

      BOOST_CHECK_CLOSE(pSquare->getValue(2, 0), spawning[0], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 1), spawning[1], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 2), spawning[2], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 3), spawning[3], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 4), spawning[4], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 5), spawning[5], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 6), spawning[6], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 7), spawning[7], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 8), spawning[8], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 9), spawning[9], 1e-9);
    }
  }
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( ProportionsAtAgeObservationWithOffByOneAgeingError, C3x3_Fixture ) {

  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(constant_recruitment_all_ages);
  addToConfiguration(annual_mortality_rate);
  addToConfiguration(category_transition_rate);
  addToConfiguration(logistic_producing);
  addToConfiguration(catchability_basic);
  addToConfiguration(string_layer);
  addToConfiguration(proportions_at_age_observation_with_off_by_one);
  addToConfiguration(constant);
  addToConfiguration(ageingerror_offbyone);
  addToTimeStep("ageing constant_recruitment_all_ages category_transition_rate annual_mortality_rate");
  BOOST_REQUIRE_NO_THROW(loadAndRunEnvironment());

  // Check our Results
  CObservationManager *pManager       = CObservationManager::Instance();
  CObservation        *pObservation   = pManager->getObservation("proportions_at_age_observation_with_off_by_one");

  vector<SComparison*> vComparisons;
  pObservation->fillComparisons(vComparisons);

  BOOST_REQUIRE_EQUAL(vComparisons.size(), 18.0);

  SComparison *pComparison = vComparisons[0];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1000, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.1, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.10456567044538505, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 589.53337351957668, 1e-9);

  pComparison = vComparisons[1];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1000, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.2, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.10448575938853867, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 1314.9728853240017, 1e-9);

  pComparison = vComparisons[2];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1000, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.7, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.79094857016607623, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 4054.1164647360665, 1e-9);

  pComparison = vComparisons[3];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaB");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1200, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.20, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.10456567044538505, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 1620.9185419325026, 1e-9);

  pComparison = vComparisons[4];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaB");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1200, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.30, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.10448575938853868, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 2575.9932899891878, 1e-9);

  pComparison = vComparisons[5];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaB");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1200, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.5, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.79094857016607623, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 3382.9887346285532, 1e-9);

  pComparison = vComparisons[6];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaC");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1300, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.30, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.10456567044538505, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 2821.2960458955786, 1e-9);

  pComparison = vComparisons[7];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaC");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1300, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.40, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.10448575938853868, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 3910.5633303565819, 1e-9);

  pComparison = vComparisons[8];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaC");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 1300, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.30, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.79094857016607623, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 2032.1631633481888, 1e-9);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      CWorldSquare *pSquare = getSquare(i,j);

      BOOST_CHECK_CLOSE(pSquare->getAbundance(), 15012.33061011306, 1e-9);

      // Our Expected Results
      double immature[] = { 1111.1111111111111, 1111.1111111111111, 1111.1111111111111, 1111.1111111111111, 1083.3333333333333, 1041.6266318250709, 952.85900493878341, 803.91670313042891, 621.10466653061906, 1404.1008649763676 };
      double mature[] = { 0.0, 0.0, 0.0, 0.0, 27.5260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531, 68.514671490004474, 153.01395904028104, 288.4780206714787, 442.52416779189696, 3680.8881270055226 };
      double spawning[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

      // Check Expected against model
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 0), immature[0], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 1), immature[1], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 2), immature[2], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 3), immature[3], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 4), immature[4], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 5), immature[5], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 6), immature[6], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 7), immature[7], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 8), immature[8], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(0, 9), immature[9], 1e-9);

      BOOST_CHECK_CLOSE(pSquare->getValue(1, 0), mature[0], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 1), mature[1], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 2), mature[2], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 3), mature[3], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 4), mature[4], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 5), mature[5], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 6), mature[6], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 7), mature[7], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 8), mature[8], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(1, 9), mature[9], 1e-9);

      BOOST_CHECK_CLOSE(pSquare->getValue(2, 0), spawning[0], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 1), spawning[1], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 2), spawning[2], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 3), spawning[3], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 4), spawning[4], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 5), spawning[5], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 6), spawning[6], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 7), spawning[7], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 8), spawning[8], 1e-9);
      BOOST_CHECK_CLOSE(pSquare->getValue(2, 9), spawning[9], 1e-9);
    }
  }
}

#endif /* TEST */
