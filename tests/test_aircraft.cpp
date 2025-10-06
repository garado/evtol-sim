
#include "../src/aircraft.hpp"
#include <gtest/gtest.h>

TEST(AircraftTest, AlphaInitialization) {
  Alpha a;
  EXPECT_EQ(a.m_cruise_speed, 120);
  EXPECT_EQ(a.m_max_battery_cap, 320);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
