
#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

/**
 * @class Simulator
 * @brief
 */
class Simulator {
public:
  Simulator() {}
  ~Simulator() = default;

  void simulate(int simtime_ms);
  void report();

private:
  int step_ms = 10;         /** Time step interval (ms) */
  int duration_ms = 180000; /** Simulation duration (ms) */
};

/**
 * @class Aircraft
 * @brief
 */
class Aircraft {
public:
  Aircraft() = default;
  ~Aircraft() = default;

private:
};

#endif /* __SIMULATOR_H__ */
