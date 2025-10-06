
# Joby take-home

## On the simulator class

## On the aircraft class
I've created a base `Aircraft` class and derived classes for each of the given aircraft.

In a more realistic aircraft simulator, each aircraft would have different behaviors - different control laws, powertrain models, aerodynamic profiles - each aircraft would have to override `update()` accounting for these different behaviors.

But since this is a simple sim, the derived classes just have the different aircraft characteristics.

## Assumptions made
**Assumed that faults are not catastrophic.** The faults being recorded cannot be catastrophic (i.e. take out of the sim immediately), because the probability of catastrophic faults per hour is 10^-9. (Or maybe they *are* catastrophic, and these are just really bad aircraft :P I'll assume this is not the case.)

**Assumed that the faults are for every mode, not just flight.**

# What I would change to make it better
