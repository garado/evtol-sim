
#ifndef __AIRCRAFT_H__
#define __AIRCRAFT_H__

/**
 * @brief Different types of aircraft.
 */
enum AircraftType {
  TYPE__ALPHA,
  TYPE__BETA,
  TYPE__CHARLIE,
  TYPE__DELTA,
  TYPE__ECHO,
  MAX_AIRCRAFT_TYPES,
};

/** @brief Stringified AircraftType enum. */
extern const char *aircraft_type_str[];

/**
 * @brief Enum for different aircraft operational modes.
 */
enum AircraftMode {
  MODE__IDLE,
  MODE__WAITING_TO_CHARGE,
  MODE__CHARGING,
  MODE__FLYING,
  MAX_AIRCRAFT_MODES,
};

/** @brief Stringified AircraftMode enum. */
extern const char *aircraft_mode_str[];

/**
 * @class Aircraft
 * @brief Stores characteristics and simulation parameters for an aircraft.
 */
class Aircraft {
protected:
  // Aircraft characterization (given)
  AircraftType m_aircraft_type;
  int m_cruise_speed;         /** Cruise speed (mph) */
  int m_max_battery_cap;      /** Battery capacity (kWh) */
  double m_charge_time;       /** Time to charge (hours) */
  double m_energy_use_cruise; /** Energy use at cruise (kWh/mile) */
  int m_max_passenger_cnt;    /** Maximum passenger count */
  double m_p_fault_hourly;    /** Probability of fault per hour */

  // Aircraft characterization (derived)
  double m_max_trip_len;       /** Maximum trip distance (miles) */
  double m_reserve_bat_target; /** Reserve battery capacity target (kWh) */
  double m_charge_per_hour;    /** kWh gained per hour of charging */

  // Simulation parameters
  double m_sim_total_miles_flown; /** Total miles flown in a run */
  double m_sim_rem_energy;        /** Remaining battery capacity (kWh) */
  int m_sim_total_num_faults;     /** Total faults in a run */
  AircraftMode m_sim_mode;        /** Current aircraft mode */
  double m_sim_trip_len;          /** Trip length (miles) */
  double m_sim_miles_traveled; /** Number of miles traveled on current trip */
  int m_sim_passenger_cnt;     /** Number of passengers for the current trip */

  void calculate_custom_params() {
    m_charge_per_hour = m_max_battery_cap / m_charge_time;
    m_max_trip_len = 1 / (m_energy_use_cruise / m_max_battery_cap);
    m_reserve_bat_target = m_max_battery_cap * 0.20;
    m_sim_rem_energy = (double)m_max_battery_cap;
  }

public:
  Aircraft() {
    m_sim_total_miles_flown = 0.0;
    m_sim_total_num_faults = 0;
    m_sim_trip_len = 0.0;
    m_sim_passenger_cnt = 0;
    m_sim_mode = MODE__IDLE;
    m_sim_trip_len = 0.0;
    m_sim_miles_traveled = 0.0;
  };

  virtual ~Aircraft() = default;

  void run(double duration_ms);

  void start_trip(int passengers, double distance);

  void fly(double duration_ms);

  void charge(double duration_ms);

  double calculate_trip_energy(double distance);

  // Getters/setters
  double get_rem_energy() { return m_sim_rem_energy; };

  AircraftType get_type() { return m_aircraft_type; };

  AircraftMode get_mode() { return m_sim_mode; };
  void set_mode(AircraftMode mode) { m_sim_mode = mode; };

  double get_trip_len() { return m_sim_trip_len; };

  void set_trip_len(int len) {
    if (len > m_max_trip_len) {
      // TODO: Error handling
      m_sim_trip_len = 0;
      return;
    }

    m_sim_trip_len = len;
  };

  double get_rem_trip_len() { return m_sim_miles_traveled; };

  double get_max_trip_len() { return m_max_trip_len; };
};

class Alpha : public Aircraft {
public:
  Alpha() {
    m_aircraft_type = TYPE__ALPHA;
    m_cruise_speed = 120;
    m_max_battery_cap = 320;
    m_charge_time = 0.6;
    m_energy_use_cruise = 1.6;
    m_max_passenger_cnt = 4;
    m_p_fault_hourly = 0.25;
    calculate_custom_params();
  }
};

class Beta : public Aircraft {
public:
  Beta() {
    m_aircraft_type = TYPE__BETA;
    m_cruise_speed = 100;
    m_max_battery_cap = 100;
    m_charge_time = 0.2;
    m_energy_use_cruise = 1.5;
    m_max_passenger_cnt = 5;
    m_p_fault_hourly = 0.10;
    calculate_custom_params();
  }
};

class Charlie : public Aircraft {
public:
  Charlie() {
    m_aircraft_type = TYPE__CHARLIE;
    m_cruise_speed = 160;
    m_max_battery_cap = 220;
    m_charge_time = 0.8;
    m_energy_use_cruise = 2.2;
    m_max_passenger_cnt = 3;
    m_p_fault_hourly = 0.05;
    calculate_custom_params();
  }
};

class Delta : public Aircraft {
public:
  Delta() {
    m_aircraft_type = TYPE__DELTA;
    m_cruise_speed = 90;
    m_max_battery_cap = 120;
    m_charge_time = 0.62;
    m_energy_use_cruise = 0.8;
    m_max_passenger_cnt = 2;
    m_p_fault_hourly = 0.22;
    calculate_custom_params();
  }
};

class Echo : public Aircraft {
public:
  Echo() {
    m_aircraft_type = TYPE__ECHO;
    m_cruise_speed = 30;
    m_max_battery_cap = 150;
    m_charge_time = 0.3;
    m_energy_use_cruise = 5.8;
    m_max_passenger_cnt = 2;
    m_p_fault_hourly = 0.61;
    calculate_custom_params();
  }
};

#endif /* __AIRCRAFT_H__ */
