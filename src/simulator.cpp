
#include "simulator.hpp"
#include "aircraft.hpp"
#include <cstring>
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
  memset(m_type_stats, 0, sizeof(m_type_stats));

  // Initialize random types of vehicles
  for (int i = 0; i < m_vehicle_count; i++) {
    AircraftType random_type = (AircraftType)(rand() % MAX_AIRCRAFT_TYPES);
    m_type_stats[random_type].type_count++;

    switch (random_type) {
    case TYPE__ALPHA:
      m_vehicles[i] = Alpha();
      break;
    case TYPE__BETA:
      m_vehicles[i] = Beta();
      break;
    case TYPE__CHARLIE:
      m_vehicles[i] = Charlie();
      break;
    case TYPE__DELTA:
      m_vehicles[i] = Delta();
      break;
    case TYPE__ECHO:
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
    std::cout << "----------------------" << std::endl;
    std::cout << "t = " << time << "ms" << std::endl;

    for (int i = 0; i < m_vehicle_count; i++) {
      update_aircraft(&m_vehicles[i]);
      report_step(&m_vehicles[i]);
    }

    m_ticks++;
  }
}

/**
 * @class Simulator
 * @brief Update state of a single aircraft
 * @param index Index of vehicle in m_vehicles
 */
void Simulator::update_aircraft(Aircraft *vehicle) {
  vehicle->m_ticks_per_mode[vehicle->m_sim_mode]++;
  vehicle->fault_chance(m_step_ms);

  // State machine for aircraft
  if (MODE__IDLE == vehicle->m_sim_mode) {
    if (vehicle->m_sim_rem_energy <= 0) {
      vehicle->m_sim_mode = MODE__WAITING_TO_CHARGE;
    } else {
      // @TODO Vary passenger count, trip length for a more realistic sim
      vehicle->start_trip(vehicle->m_max_passenger_cnt,
                          vehicle->m_max_trip_len);
    }
  } else if (MODE__FLYING == vehicle->m_sim_mode) {
    vehicle->fly(m_step_ms);
  } else if (MODE__CHARGING == vehicle->m_sim_mode) {
    vehicle->charge(m_step_ms);
  } else if (MODE__WAITING_TO_CHARGE == vehicle->m_sim_mode) {
    if (m_num_chargers_in_use < m_charger_count) {
      m_num_chargers_in_use++;
      vehicle->set_mode(MODE__CHARGING);
    } else {
      vehicle->m_sim_ticks_waiting_chg++;
    }
  } else if (MODE__CHARGE_COMPLETE == vehicle->m_sim_mode) {
    m_num_chargers_in_use--;
    vehicle->set_mode(MODE__IDLE);
    charge_next_aircraft();
  }
}

void Simulator::charge_next_aircraft() {
  int longest_wait = -1;
  int longest_wait_index = -1;

  for (int i = 0; i < m_vehicle_count; i++) {
    if (MODE__WAITING_TO_CHARGE == m_vehicles[i].m_sim_mode) {
      if (m_vehicles[i].m_sim_ticks_waiting_chg > longest_wait) {
        longest_wait = m_vehicles[i].m_sim_ticks_waiting_chg;
        longest_wait_index = i;
      }
    }
  }

  if (longest_wait > -1) {
    m_num_chargers_in_use++;
    m_vehicles[longest_wait_index].set_mode(MODE__CHARGING);
  }
}

/**
 * @class Simulator
 * @brief Output CSV report of how long each vehicle spent in each mode.
 */
void Simulator::report_mode_results() {
  std::cout << "VehicleNumber,VehicleType,Idle,Wait_Chg,Chg_Done,Fly"
            << std::endl;

  Aircraft *vehicle;

  for (int i = 0; i < m_vehicle_count; i++) {
    vehicle = &m_vehicles[i];
    std::cout << i << "," << aircraft_type_str[vehicle->get_type()] << ",";

    for (int j = 0; j < MAX_AIRCRAFT_MODES; j++) {
      std::cout << (double)vehicle->get_mode_stats()[j] / m_ticks << ",";
    }

    std::cout << std::endl;
  }
}

/**
 * @class Simulator
 * @brief Report human-readable vehicle stats for a single timestep of the
 * simulation. Mostly for debugging.
 */
void Simulator::report_step(Aircraft *vehicle) {
  std::cout << std::fixed << std::setprecision(5) << "["
            << aircraft_type_str[vehicle->get_type()] << "] "
            << aircraft_mode_str[vehicle->get_mode()]
            << " (rem: " << vehicle->get_rem_energy()
            << "; trip: " << vehicle->get_rem_trip_len() << "/"
            << vehicle->get_trip_len() << ")" << std::endl;
}

/**
 * @class Simulator
 * @brief Output CSV report of aggregate vehicle type statistics, per the
 * problem description.
 */
void Simulator::report_vehicle_type_stats() {
  std::cout << "VehicleType,VehicleCount,FlightTimePerFlight,DistPerFlight,"
               "ChgSessionTime,"
               "TotalFaults,TotalPassengerMiles"
            << std::endl;

  for (int i_type = 0; i_type < MAX_AIRCRAFT_TYPES; i_type++) {
    std::cout << aircraft_type_str[i_type] << ",";

    int vehicle_count = 0;
    double flight_time = 0.0;
    double distance_per_flight = 0.0;
    double chg_session_time = 0.0;
    int total_faults = 0;
    int total_passenger_miles = 0;

    for (int j_vehicle = 0; j_vehicle < 20; j_vehicle++) {
      if (i_type == m_vehicles[j_vehicle].get_type()) {
        vehicle_count++;
        total_passenger_miles += m_vehicles[j_vehicle].get_total_passenger_mi();
        total_faults += m_vehicles[j_vehicle].m_sim_total_num_faults;
      }
    }

    std::cout << vehicle_count << "," << flight_time / vehicle_count << ","
              << distance_per_flight / vehicle_count << ","
              << chg_session_time / vehicle_count << ","
              << total_faults / vehicle_count << "," << total_passenger_miles
              << std::endl;
  }
}
