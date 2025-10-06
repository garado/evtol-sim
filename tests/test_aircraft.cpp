
#include "../src/aircraft.hpp"
#include "../src/common.hpp"
#include <gtest/gtest.h>

// A few quick tests to demonstrate how I'd use gtest to unit test.

/**
 * @brief Verify aircraft correctly completes a trip and transitions to IDLE.
 *
 * - The aircraft mode transitions to MODE__IDLE upon trip completion
 * - Total miles flown equals the trip distance
 * - Passenger-miles are correctly calculated (distance × passengers)
 * - Battery energy is consumed during flight
 */
TEST(AircraftTest, FlyCompletesTrip) {
  Alpha alpha;

  // 120mi / 120mph cruise speed = 1 hour to complete
  alpha.start_trip(4, 120.0);

  double initial_energy = alpha.m_sim_rem_energy;

  // Fly for exactly 1 hour
  alpha.fly(MS_PER_HOUR);

  EXPECT_EQ(alpha.m_sim_mode, MODE__IDLE);
  EXPECT_DOUBLE_EQ(alpha.m_sim_total_miles, 120.0);
  EXPECT_DOUBLE_EQ(alpha.m_sim_total_passenger_mi, 480.0); // 120 * 4
  EXPECT_LT(alpha.m_sim_rem_energy, initial_energy);
}

/**
 * @brief Test behavior during complete depletion of battery while flying.
 *
 * - Aircraft transitions to WAITING_TO_CHARGE after running out of battery
 * - Temaining energy correctly goes to 0 for no battery power remaining
 * - Counter for miles traveled reflects partial distance traveled
 */
TEST(AircraftTest, FlyDepletesBattery) {
  Alpha alpha;
  alpha.m_sim_rem_energy = 50.0; // Low battery

  // 200mi / 120mph cruise = 1.667hours to complete
  alpha.start_trip(4, 200.0);

  // Fly until battery runs out
  alpha.fly(MS_PER_HOUR * 2); // Any time > 1.667hours

  EXPECT_EQ(alpha.m_sim_mode, MODE__WAITING_TO_CHARGE);
  EXPECT_DOUBLE_EQ(alpha.m_sim_rem_energy, 0.0);

  // Should only fly partial distance: 50 kWh / 1.6 kWh/mi = 31.25 miles
  EXPECT_DOUBLE_EQ(alpha.m_sim_total_miles, 31.25);
  EXPECT_DOUBLE_EQ(alpha.m_sim_total_passenger_mi, 125.0); // 31.25 * 4 pass.
}

/**
 * @brief Verify aircraft correctly handles flight during a normal timestep.
 * i.e. one that doesn't complete the flight.
 *
 * - The aircraft remains in MODE__FLYING (does not complete trip)
 * - Miles traveled are calculated correctly for the given timestep
 * - Trip progress (m_sim_trip_miles_elapsed) is updated accurately
 * - Energy consumption matches the distance traveled
 */
TEST(AircraftTest, FlyTimestep) {
  Charlie charlie;
  charlie.start_trip(3, 100.0);

  // Fly for 5 minutes: should travel 160 mph * (5/60) hr = 13.33 miles
  double initial_energy = charlie.m_sim_rem_energy;
  charlie.fly(MS_PER_MIN * 5);

  EXPECT_EQ(charlie.m_sim_mode, MODE__FLYING);
  EXPECT_NEAR(charlie.m_sim_trip_miles_elapsed, 13.333, 0.01);
  EXPECT_NEAR(charlie.m_sim_total_miles, 13.333, 0.01);

  // Energy used: 2.2 kWh/mi * 13.33 mi = 29.33 kWh
  EXPECT_NEAR(charlie.m_sim_rem_energy, initial_energy - 29.33, 0.5);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
