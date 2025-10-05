
#include "simulator.hpp"
#include "aircraft.hpp"
#include <iomanip>
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
    std::cout << "t = " << time << "ms" << std::endl;

    for (int i = 0; i < m_vehicle_count; i++) {
      update_aircraft(i);
    }
  }
}

/**
 * @class Simulator
 * @brief Update state of a single aircraft
 * @param index Index of vehicle in m_vehicles
 */
void Simulator::update_aircraft(int index) {
  Aircraft *vehicle = &m_vehicles[index];

  if (MODE__IDLE == vehicle->get_mode()) {
    // Initialize new trip
    int new_trip_len = rand() % (int)vehicle->get_max_trip_len();
    vehicle->set_trip_len(new_trip_len);
  } else if (MODE__FLYING) {
    vehicle->update(m_step_ms);
  } else if (MODE__CHARGING) {

  } else if (MODE__WAITING_TO_CHARGE) {
  }

  // Reporting
  std::cout << std::setw(2) << std::setfill('0') << index << ". "
            << "[" << aircraft_type_str[vehicle->get_type()] << "] "
            << aircraft_mode_str[vehicle->get_mode()]
            << " (rem: " << vehicle->get_rem_energy()
            << "; trip: " << vehicle->get_rem_trip_len() << "/"
            << vehicle->get_trip_len() << ")" << std::endl;
}

/**
 * @class Simulator
 * @brief Output simulation report.
 */
void Simulator::report() {
  std::cout << "Reporting simulation results" << std::endl;
}
