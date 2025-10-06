/**
 * @file simulator.hpp
 * @brief Simulator class definition.
 */

#ifndef SIMULATOR_H
#define SIMULATOR_H

/*****************************************************************
 * Includes
 *****************************************************************/

#include "aircraft.hpp"
#include "common.hpp"

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
 * Constants
 *****************************************************************/

constexpr int MAX_VEHICLES = 20;
constexpr int MAX_CHARGERS = 3;

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

private:
  int m_vehicle_count = MAX_VEHICLES; /** Vehicles to use in simulation */
  int m_charger_count = MAX_CHARGERS; /** Available chargers */
  int m_num_chargers_in_use = 0;      /** Chargers actively being used */
  Aircraft m_vehicles[MAX_VEHICLES];  /** Data for simulated vehicles */
  int m_ticks = 0;                    /** Total elapsed simulation ticks */
  int m_step_ms = 100;                /** Time step interval (ms) */

  /**
   * @class Simulator
   * @brief Find the next aircraft to charge, and charge it. FIFO waiting queue.
   */
  void charge_next_aircraft();
};

#endif /* SIMULATOR_H */
