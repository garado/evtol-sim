
#ifndef __AIRCRAFT_H__
#define __AIRCRAFT_H__

enum AircraftType {
  ALPHA,
  BETA,
  CHARLIE,
  DELTA,
  ECHO,
  MAX_AIRCRAFT_TYPES,
};

static const char *aircraft_type_str[] = {
    "Alpha", "Beta", "Charlie", "Delta", "Echo",
};

/**
 * @class Aircraft
 * @brief Represents a vehicle
 */
class Aircraft {
public:
  Aircraft() = default;
  virtual ~Aircraft() = default;

  void simulate();

  // Getters/setters
  AircraftType get_type() { return m_aircraft_type; };

protected:
  // Aircraft characterization
  AircraftType m_aircraft_type;
  int m_cruise_speed;         /** Cruise speed (mph) */
  int m_battery_cap;          /** Battery capacity (kWh) */
  double m_charge_time;       /** Time to charge (hours) */
  double m_energy_use_cruise; /** Energy use at cruise (kWh/mile) */
  int m_passenger_count;      /** Passenger count */
  double m_p_fault_hourly;    /** Probability of fault per hour */

  // Simulation parameters
};

class Alpha : public Aircraft {
public:
  Alpha() {
    m_aircraft_type = ALPHA;
    m_cruise_speed = 120;
    m_battery_cap = 320;
    m_charge_time = 0.6;
    m_energy_use_cruise = 1.6;
    m_passenger_count = 4;
    m_p_fault_hourly = 0.25;
  }
};

class Beta : public Aircraft {
public:
  Beta() {
    m_aircraft_type = BETA;
    m_cruise_speed = 100;
    m_battery_cap = 100;
    m_charge_time = 0.2;
    m_energy_use_cruise = 1.5;
    m_passenger_count = 5;
    m_p_fault_hourly = 0.10;
  }
};

class Charlie : public Aircraft {
public:
  Charlie() {
    m_aircraft_type = CHARLIE;
    m_cruise_speed = 160;
    m_battery_cap = 220;
    m_charge_time = 0.8;
    m_energy_use_cruise = 2.2;
    m_passenger_count = 3;
    m_p_fault_hourly = 0.05;
  }
};

class Delta : public Aircraft {
public:
  Delta() {
    m_aircraft_type = DELTA;
    m_cruise_speed = 90;
    m_battery_cap = 120;
    m_charge_time = 0.62;
    m_energy_use_cruise = 0.8;
    m_passenger_count = 2;
    m_p_fault_hourly = 0.22;
  }
};

class Echo : public Aircraft {
public:
  Echo() {
    m_aircraft_type = ECHO;
    m_cruise_speed = 30;
    m_battery_cap = 150;
    m_charge_time = 0.3;
    m_energy_use_cruise = 5.8;
    m_passenger_count = 2;
    m_p_fault_hourly = 0.61;
  }
};

#endif /* __AIRCRAFT_H__ */
