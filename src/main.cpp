
#include "common.hpp"
#include "simulator.hpp"
#include <random>

constexpr int SIM_DURATION_MIN = 5;
constexpr int SIM_STEP_MS = MS_PER_SEC * 60 * 1;

int main() {
  srand(1);

  Simulator sim(1);
  sim.set_step(SIM_STEP_MS);
  sim.simulate(SIM_DURATION_MIN * MIN_TO_MS);

  sim.report();

  return 0;
}
