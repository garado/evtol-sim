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
  int m_ticks = 0;                    /** Total elapsed simulation ticks */
  int m_step_ms = 100;                /** Time step interval (ms) */

  /** Data for simulated vehicles.
   * @note This is slicing, but the simulation still works as intended
   * because the derived classes do not have any data/custom behavior of their
   * own, and just update base class variables. This would need to be fixed if
   * this were not the case.
   *
   * I don't particularly want to refactor everything right now.
   * But the correct thing to do would be:
   * std::unique_ptr<Aircraft> m_vehicles[MAX_VEHICLES];
   **/
  Aircraft m_vehicles[MAX_VEHICLES];

  /**
   * @class Simulator
   * @brief Find the next aircraft to charge, and charge it. FIFO waiting queue.
   */
  void allocate_charger_fifo();
};

#endif /* SIMULATOR_H */
