/**
 * @file aircraft.cpp
 * @brief Aircraft class implementation.
 *
 * Contains the logic for different aircraft functions and operational
 * modes.
 */

/*****************************************************************
 * Includes
 *****************************************************************/

#include "aircraft.hpp"
#include "common.hpp"
#include <cstdlib>

/*****************************************************************
 *
 *****************************************************************/

const char *aircraft_type_str[] = {
    "Alpha", "Beta", "Charlie", "Delta", "Echo",
};

const char *aircraft_mode_str[] = {
    "IDLE", "WAIT_CHG", "CHG_DONE", "CHG", "FLY",
};

/*****************************************************************
 * Member function definitions
 *****************************************************************/

/**
 * @class Aircraft
 * @brief Initialize a trip.
 * @param passengers Number of passengers for current trip
 * @param distance Distance (miles) for current trip
 */
void Aircraft::start_trip(int passengers, double distance) {
  m_sim_trip_passenger_cnt = passengers;
  m_sim_trip_len = distance;
  m_sim_trip_miles_elapsed = 0;
  m_sim_mode = MODE__FLYING;
}

/**
 * @class Aircraft
 * @brief Calculate fault chance.
 * @param duration_ms The duration for which to calculate the fault probability.
 */
void Aircraft::fault_chance(double duration_ms) {
  double fault_prob = (duration_ms / MS_PER_HOUR) * m_p_fault_hourly;

  if ((double)rand() / RAND_MAX < fault_prob) {
    m_sim_total_num_faults++;
  }
}

/**
 * @class Aircraft
 * @brief Update flight parameters.
 * @param duration_ms The duration for which to update flight parameters.
 */
void Aircraft::fly(double duration_ms) {
  double capacity_used = m_energy_use_cruise * m_cruise_speed *
                         (duration_ms / (double)MS_PER_HOUR);

  double miles_traveled = m_cruise_speed * (duration_ms / (double)MS_PER_HOUR);

  m_sim_trip_flight_time_ms += duration_ms;

  if (capacity_used > m_sim_rem_energy) {
    m_sim_mode = MODE__WAITING_TO_CHARGE;
  } else {
    if ((m_sim_trip_miles_elapsed + miles_traveled) >= m_sim_trip_len) {
      m_sim_mode = MODE__IDLE; // Trip complete
    }

    m_sim_rem_energy -= capacity_used;
    m_sim_trip_miles_elapsed += miles_traveled;
    m_sim_total_passenger_mi += miles_traveled * m_sim_trip_passenger_cnt;
  }
}

/**
 * @class Aircraft
 * @brief Charge the aircraft.
 * @param duration_ms The duration for which to charge the aircraft.
 */
void Aircraft::charge(double duration_ms) {
  double amount_charged = (duration_ms / MS_PER_HOUR) * m_charge_per_hour;

  if ((m_sim_rem_energy + amount_charged) > m_max_battery_cap) {
    m_sim_rem_energy = m_max_battery_cap;
  } else {
    m_sim_rem_energy += amount_charged;
  }

  if (m_sim_rem_energy == m_max_battery_cap) {
    m_sim_mode = MODE__CHARGE_COMPLETE;
  }
}
