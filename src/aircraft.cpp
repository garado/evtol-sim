
#include "aircraft.hpp"
#include <iostream>

constexpr int MS_PER_HOUR = 60 * 60 * 1000;

const char *aircraft_type_str[] = {
    "Alpha", "Beta", "Charlie", "Delta", "Echo",
};

const char *aircraft_mode_str[] = {
    "Idle",
    "Waiting to charge",
    "Charging",
    "Flying",
};

/**
 * @class Aircraft
 * @brief Run aircraft state machine for a specified duration
 * @param duration_ms
 */
void Aircraft::run(double duration_ms) {
  if (MODE__IDLE == m_sim_mode) {
    if (m_sim_rem_energy <= m_reserve_bat_target) {
      m_sim_mode = MODE__WAITING_TO_CHARGE;
    } else {
      // int new_trip_len = rand() % (int)vehicle->get_max_trip_len();
      start_trip(m_max_passenger_cnt, 30);
    }
  } else if (MODE__FLYING == m_sim_mode) {
    fly(duration_ms);
  } else if (MODE__CHARGING == m_sim_mode) {
  } else if (MODE__WAITING_TO_CHARGE == m_sim_mode) {
  }
}

/**
 * @class Aircraft
 * @brief
 */
void Aircraft::start_trip(int passengers, double distance) {
  m_sim_passenger_cnt = passengers;
  m_sim_trip_len = distance;
  m_sim_miles_traveled = 0;
  m_sim_mode = MODE__FLYING;
}

/**
 * @class Aircraft
 * @brief Update flight parameters
 */
void Aircraft::fly(double duration_ms) {
  double capacity_used = m_energy_use_cruise * m_cruise_speed *
                         (duration_ms / (double)MS_PER_HOUR);

  double miles_traveled = m_cruise_speed * (duration_ms / (double)MS_PER_HOUR);

  if (capacity_used > m_sim_rem_energy) {
    // @TODO Not enough battery to travel this duration (this shouldn't happen)
  } else if ((m_sim_miles_traveled + miles_traveled) >= m_sim_trip_len) {
    // The trip is done
    m_sim_mode = MODE__IDLE;
    m_sim_rem_energy -= capacity_used;
    m_sim_miles_traveled += miles_traveled;
    m_sim_total_miles_flown += miles_traveled;
  } else {
    // Trip still in progress
    m_sim_rem_energy -= capacity_used;
    m_sim_miles_traveled += miles_traveled;
    m_sim_total_miles_flown += miles_traveled;
  }
}
