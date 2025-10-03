
#include "simulator.hpp"
#include <iostream>

/**
 * @class Simulator
 * @brief Run a simulation.
 * @param duration_ms Sim time, in milliseconds
 */
void Simulator::simulate(int duration_ms) {
  std::cout << "Simulating for " << duration_ms << "ms" << std::endl;
}

/**
 * @class Simulator
 * @brief Output simulation report.
 */
void Simulator::report() {
  std::cout << "Reporting simulation results" << std::endl;
}
