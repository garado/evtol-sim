
#include "simulator.hpp"
#include <iostream>

int main() {
  Simulator sim;
  sim.simulate(10);

  sim.report();

  return 0;
}
