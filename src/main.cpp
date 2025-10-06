/**
 * @file main.cpp
 * @brief Entry point for program.
 */

/*****************************************************************
 * Includes
 *****************************************************************/

#include "common.hpp"
#include "simulator.hpp"
#include <cstdlib>

/*****************************************************************
 * Constants
 *****************************************************************/

constexpr int SIM_DURATION_MS = MS_PER_HOUR * 3;

/*****************************************************************
 * Function definitions
 *****************************************************************/

int main() {
  srand(532);

  Simulator sim(MAX_VEHICLES);
  sim.simulate(SIM_DURATION_MS);

  // sim.report_time_per_mode();
  sim.report_vehicle_type_stats();

  return 0;
}
