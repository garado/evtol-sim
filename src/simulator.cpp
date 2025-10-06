/**
 * @file simulator.cpp
 * @brief Simulator class implementation.
 *
 * Contains the simulation logic for managing multiple aircraft,
 * charging stations, and collecting statistics.
 */

/*****************************************************************
 * Includes
 *****************************************************************/

#include "simulator.hpp"
#include "aircraft.hpp"
#include "common.hpp"
#include <cstring>
#include <iomanip>
#include <iostream>

/*****************************************************************
 * Member function definitions
 *****************************************************************/

/**
 * @class Simulator
 * @brief Constructor for simulator.
 * @param vehicle_count Number of vehicles in the simulator.
 *
 * Initializes `m_vehicle_count` random aircraft.
 */
Simulator::Simulator(int vehicle_count) {
  if (vehicle_count > MAX_VEHICLES) {
    vehicle_count = MAX_VEHICLES;
  }

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
    case TYPE__BRAVO:
      m_vehicles[i] = Bravo();
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
  vehicle->m_mode_ticks[vehicle->m_sim_mode]++;
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
      vehicle->m_sim_charging_sessions++;
      vehicle->m_sim_mode = MODE__CHARGING;
    } else {
      vehicle->m_sim_ticks_waiting_chg++;
    }
  } else if (MODE__CHARGE_COMPLETE == vehicle->m_sim_mode) {
    m_num_chargers_in_use--;
    vehicle->m_sim_mode = MODE__IDLE;
    charge_next_aircraft();
  }
}

/**
 * @class Simulator
 * @brief Find the next aircraft to charge, and charge it. FIFO waiting queue.
 */
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

  if (longest_wait_index > -1) {
    m_num_chargers_in_use++;
    m_vehicles[longest_wait_index].m_sim_charging_sessions++;
    m_vehicles[longest_wait_index].m_sim_mode = MODE__CHARGING;
  }
}

/**
 * @class Simulator
 * @brief Output CSV report of how long each vehicle spent in each mode.
 */
void Simulator::report_time_per_mode() {
  std::cout << "VehicleNumber,VehicleType,Idle,Wait_Chg,Chg_Done,Chg,Fly"
            << std::endl;

  Aircraft *vehicle;

  for (int i = 0; i < m_vehicle_count; i++) {
    vehicle = &m_vehicles[i];
    std::cout << i << "," << aircraft_type_str[vehicle->m_type] << ",";

    for (int j = 0; j < MAX_AIRCRAFT_MODES; j++) {
      std::cout << (double)vehicle->m_mode_ticks[j] / m_ticks << ",";
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
            << aircraft_type_str[vehicle->m_type] << "] "
            << aircraft_mode_str[vehicle->m_sim_mode]
            << " (rem: " << vehicle->m_sim_rem_energy
            << "; trip: " << vehicle->m_sim_trip_miles_elapsed << "/"
            << vehicle->m_sim_trip_len << ")" << std::endl;
}

/**
 * @class Simulator
 * @brief Output CSV report of aggregate vehicle type statistics, per the
 * problem description.
 */
void Simulator::report_vehicle_type_stats() {
  std::cout
      << "VehicleType,VehicleCount,FlightTimePerFlight(Hours),DistPerFlight,"
         "ChgSessionTime,"
         "TotalFaults,TotalPassengerMiles"
      << std::endl;

  for (int i_type = 0; i_type < MAX_AIRCRAFT_TYPES; i_type++) {
    std::cout << aircraft_type_str[i_type] << ",";

    // Aggregate these statistics for each vehicle of this type
    int vehicle_count = 0;
    double total_flight_time = 0.0;
    int total_num_flights = 0;
    double total_flight_distance = 0.0;
    double total_chg_time = 0.0;
    int total_faults = 0;
    int total_passenger_miles = 0;
    int total_chg_sessions = 0;

    for (int j_vehicle = 0; j_vehicle < m_vehicle_count; j_vehicle++) {
      Aircraft *vehicle = &m_vehicles[j_vehicle];

      if (i_type == vehicle->m_type) {
        vehicle_count++;
        total_passenger_miles += vehicle->m_sim_total_passenger_mi;
        total_faults += vehicle->m_sim_total_num_faults;
        total_num_flights += vehicle->m_sim_trips_started;
        total_flight_distance += vehicle->m_sim_total_miles;
        total_chg_sessions += vehicle->m_sim_charging_sessions;

        total_flight_time += (vehicle->m_mode_ticks[MODE__FLYING] * m_step_ms) /
                             (double)MS_PER_HOUR;

        total_chg_time += (vehicle->m_mode_ticks[MODE__CHARGING] * m_step_ms) /
                          (double)MS_PER_HOUR;
      }
    }

    double avg_flight_time;
    double avg_flight_dist;
    double avg_chg_time;

    if (total_num_flights > 0) {
      avg_flight_time = total_flight_time / (double)total_num_flights;
    } else {
      avg_flight_time = 0;
    }

    if (total_num_flights > 0) {
      avg_flight_dist = total_flight_distance / (double)total_num_flights;
    } else {
      avg_flight_dist = 0;
    }

    if (total_chg_sessions > 0) {
      avg_chg_time = total_chg_time / (double)total_chg_sessions;
    } else {
      avg_chg_time = 0;
    }

    std::cout << vehicle_count << "," << avg_flight_time << ","
              << avg_flight_dist << "," << avg_chg_time << "," << total_faults
              << "," << total_passenger_miles << std::endl;
  }
}
