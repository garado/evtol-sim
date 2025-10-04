
#ifndef __AIRCRAFT_H__
#define __AIRCRAFT_H__

/**
 * @class Aircraft
 * @brief Represents a vehicle
 */
class Aircraft {
public:
  Aircraft() = default;
  ~Aircraft() = default;
  void simulate();

private:
  // Aircraft characterization
  int m_cruise_speed;         /** Cruise speed (mph) */
  int m_battery_cap;          /** Battery capacity (kWh) */
  double m_charge_time;       /** Time to charge (hours) */
  double m_energy_use_cruise; /** Energy use at cruise (kWh/mile) */
  int m_passenger_count;      /** Passenger count */
  double m_p_fault_hourly;    /** Probability of fault per hour */

  // Simulation parameters
};

class Alpha : public Aircraft {
private:
  int m_cruise_speed = 120;         /** Cruise speed (mph) */
  int m_battery_cap = 320;          /** Battery capacity (kWh) */
  double m_charge_time = 0.6;       /** Time to charge (hours) */
  double m_energy_use_cruise = 1.6; /** Energy use at cruise (kWh/mile) */
  int m_passenger_count = 4;        /** Passenger count */
  double m_p_fault_hourly = 0.25;   /** Probability of fault per hour */
};

class Beta : public Aircraft {
private:
  int m_cruise_speed = 100;         /** Cruise speed (mph) */
  int m_battery_cap = 100;          /** Battery capacity (kWh) */
  double m_charge_time = 0.2;       /** Time to charge (hours) */
  double m_energy_use_cruise = 1.5; /** Energy use at cruise (kWh/mile) */
  int m_passenger_count = 5;        /** Passenger count */
  double m_p_fault_hourly = 0.10;   /** Probability of fault per hour */
};

class Charlie : public Aircraft {
private:
  int m_cruise_speed = 160;         /** Cruise speed (mph) */
  int m_battery_cap = 220;          /** Battery capacity (kWh) */
  double m_charge_time = 0.8;       /** Time to charge (hours) */
  double m_energy_use_cruise = 2.2; /** Energy use at cruise (kWh/mile) */
  int m_passenger_count = 3;        /** Passenger count */
  double m_p_fault_hourly = 0.05;   /** Probability of fault per hour */
};

class Delta : public Aircraft {
private:
  int m_cruise_speed = 90;          /** Cruise speed (mph) */
  int m_battery_cap = 120;          /** Battery capacity (kWh) */
  double m_charge_time = 0.62;      /** Time to charge (hours) */
  double m_energy_use_cruise = 0.8; /** Energy use at cruise (kWh/mile) */
  int m_passenger_count = 2;        /** Passenger count */
  double m_p_fault_hourly = 0.22;   /** Probability of fault per hour */
};

class Echo : public Aircraft {
private:
  int m_cruise_speed = 30;          /** Cruise speed (mph) */
  int m_battery_cap = 150;          /** Battery capacity (kWh) */
  double m_charge_time = 0.3;       /** Time to charge (hours) */
  double m_energy_use_cruise = 5.8; /** Energy use at cruise (kWh/mile) */
  int m_passenger_count = 2;        /** Passenger count */
  double m_p_fault_hourly = 0.61;   /** Probability of fault per hour */
};

#endif /* __AIRCRAFT_H__ */
