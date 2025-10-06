
#include "../src/aircraft.hpp"
#include "../src/common.hpp"
#include <gtest/gtest.h>

// A few quick tests to demonstrate how I'd use gtest to unit test.

TEST(AircraftTest, AlphaInitialization) {
  Alpha a;
  EXPECT_EQ(a.m_cruise_speed, 120);
  EXPECT_EQ(a.m_max_battery_cap, 320);
}

TEST(AircraftTest, FlightDepletesEnergy) {
  Alpha alpha;
  double initial_energy = alpha.m_sim_rem_energy;

  alpha.start_trip(4, 50.0);
  alpha.fly(MS_PER_HOUR * 0.5);

  EXPECT_LT(alpha.m_sim_rem_energy, initial_energy);
  EXPECT_GT(alpha.m_sim_total_miles, 0.0);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
