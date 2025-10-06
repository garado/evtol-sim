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

constexpr int SIM_DURATION_MIN = 5;
constexpr int SIM_STEP_MS = MS_PER_SEC * 60 * 1;

/*****************************************************************
 * Function definitions
 *****************************************************************/

int main() {
  srand(20);

  Simulator sim(20);
  sim.m_step_ms = SIM_STEP_MS;
  sim.simulate(SIM_DURATION_MIN * MIN_TO_MS);

  // sim.report_mode_results();
  sim.report_vehicle_type_stats();

  return 0;
}
