
#include "aircraft.hpp"
#include <iostream>

constexpr int MS_PER_HOUR = 60 * 60 * 1000;

/**
 * @class Aircraft
 * @brief Update params
 */
void Aircraft::update(double duration_ms) {
  double capacity_used = m_energy_use_cruise * m_cruise_speed *
                         (duration_ms / (double)MS_PER_HOUR);

  if (capacity_used > m_sim_rem_energy) {
  } else {
  }
}
