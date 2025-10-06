/**
 * @file simulator.hpp
 * @brief Simulator class definition.
 */

#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

/*****************************************************************
 * Includes
 *****************************************************************/

#include "aircraft.hpp"

/*****************************************************************
 * Enums and structs
 *****************************************************************/

typedef struct type_stats_t {
  int type_count;
  double flight_time_per_flight;
  double dist_per_flight;
  double chg_session_time;
  int num_faults;
  double passenger_mi;
} type_stats_t;

/*****************************************************************
 * Class definition
 *****************************************************************/

/**
 * @class Simulator
 * @brief Simulates a fleet of aircraft.
 */
class Simulator {
public:
  Simulator(int vehicle_count);
  ~Simulator() = default;

  /**
   * @class Simulator
   * @brief Run a complete simulation.
   * @param duration_ms Sim time, in milliseconds
   */
  void simulate(int simtime_ms);

  /**
   * @class Simulator
   * @brief Update state of a single aircraft
   * @param index Index of vehicle in m_vehicles
   */
  void update_aircraft(Aircraft *vehicle);

  /**
   * @class Simulator
   * @brief Output CSV report of how long each vehicle spent in each mode.
   */
  void report_time_per_mode();

  /**
   * @class Simulator
   * @brief Output CSV report of aggregate vehicle type statistics, per the
   * problem description.
   */
  void report_vehicle_type_stats();

  /**
   * @class Simulator
   * @brief Report human-readable vehicle stats for a single timestep of the
   * simulation. Mostly for debugging.
   */
  void report_step(Aircraft *vehicle);

  int m_step_ms = 10; /** Time step interval (ms) */

private:
  int m_vehicle_count = 20; /** Number of vehicles to use in the simulation */
  int m_charger_count = 3;  /** Number of available chargers */
  int m_num_chargers_in_use = 0; /** Number of chargers actively being used */
  Aircraft m_vehicles[20];       /** Vehicles being simulated */
  int m_ticks = 0;
  type_stats_t m_type_stats[MAX_AIRCRAFT_TYPES];

  void charge_next_aircraft();
};

#endif /* __SIMULATOR_H__ */
