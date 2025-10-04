
#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

#include "aircraft.hpp"

/**
 * @class Simulator
 * @brief
 */
class Simulator {
public:
  Simulator(int vehicle_count);
  ~Simulator();

  void simulate(int simtime_ms);
  void report();

private:
  int m_step_ms = 10;       /** Time step interval (ms) */
  int m_vehicle_count = 20; /** Number of vehicles to use in the simulation */
  Aircraft m_vehicles[20];
};

#endif /* __SIMULATOR_H__ */
