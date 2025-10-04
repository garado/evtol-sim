
#include "simulator.hpp"
#include "aircraft.hpp"
#include <iostream>

/**
 * @class Simulator
 * @brief Constructor for simulator.
 * @param vehicle_count Number of vehicles in the simulator.
 *
 * Initializes `m_vehicle_count` random aircraft.
 */
Simulator::Simulator(int vehicle_count) {
  m_vehicle_count = vehicle_count;

  // Initialize random types of vehicles
  srand(1);
  for (int i = 0; i < m_vehicle_count; i++) {
    int random_num = rand() % 5;

    switch (random_num) {
    case 0:
      m_vehicles[i] = Alpha();
      break;
    case 1:
      m_vehicles[i] = Beta();
      break;
    case 2:
      m_vehicles[i] = Charlie();
      break;
    case 3:
      m_vehicles[i] = Delta();
      break;
    case 4:
      m_vehicles[i] = Echo();
      break;
    default:
      break;
    }
  }

  for (int i = 0; i < m_vehicle_count; i++) {
    std::cout << aircraft_type_str[m_vehicles[i].get_type()] << std::endl;
  }
}

/**
 * @class Simulator
 * @brief Destructor for simulator.
 */
Simulator::~Simulator() {}

/**
 * @class Simulator
 * @brief Run a complete simulation.
 * @param duration_ms Sim time, in milliseconds
 */
void Simulator::simulate(int duration_ms) {
  std::cout << "Simulating for " << duration_ms << "ms" << std::endl;

  for (int time = 0; time < duration_ms; time += m_step_ms) {
  }
}

/**
 * @class Simulator
 * @brief Output simulation report.
 */
void Simulator::report() {
  std::cout << "Reporting simulation results" << std::endl;
}
