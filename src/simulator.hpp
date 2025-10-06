
#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

#include "aircraft.hpp"

typedef struct type_stats_t {
  int type_count;
  double flight_time_per_flight;
  double dist_per_flight;
  double chg_session_time;
  int num_faults;
  double passenger_mi;
} type_stats_t;

/**
 * @class Simulator
 * @brief
 */
class Simulator {
public:
  Simulator(int vehicle_count);
  ~Simulator();

  void simulate(int simtime_ms);
  void update_aircraft(Aircraft *vehicle);

  void report_mode_results();

  void report_vehicle_type_stats();

  void report_step(Aircraft *vehicle);

  // Getters/setters
  void set_step(int step_ms) { m_step_ms = step_ms; };

private:
  int m_step_ms = 10;       /** Time step interval (ms) */
  int m_vehicle_count = 20; /** Number of vehicles to use in the simulation */
  int m_charger_count = 3;  /** Number of available chargers */
  int m_num_chargers_in_use = 0; /** Number of chargers actively being used */
  Aircraft m_vehicles[20];       /** Vehicles being simulated */
  int m_ticks = 0;
  type_stats_t m_type_stats[MAX_AIRCRAFT_TYPES];

  void charge_next_aircraft();
};

#endif /* __SIMULATOR_H__ */
