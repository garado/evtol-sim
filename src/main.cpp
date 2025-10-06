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
constexpr int SIM_STEP_MS = MS_PER_SEC * 30;

/*****************************************************************
 * Function definitions
 *****************************************************************/

int main() {
  srand(532);

  Simulator sim(MAX_VEHICLES);
  sim.m_step_ms = SIM_STEP_MS;
  sim.simulate(SIM_DURATION_MS);

  // sim.report_time_per_mode();
  sim.report_vehicle_type_stats();

  return 0;
}
