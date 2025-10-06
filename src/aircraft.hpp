/**
 * @file aircraft.hpp
 * @brief Aircraft class definition.
 */

#ifndef AIRCRAFT_H
#define AIRCRAFT_H

/*****************************************************************
 * Includes
 *****************************************************************/

#include <cstring>

/*****************************************************************
 * Enums and structs
 *****************************************************************/

/** @brief Enumerate the different types of aircraft. */
enum AircraftType {
  TYPE__ALPHA,
  TYPE__BRAVO,
  TYPE__CHARLIE,
  TYPE__DELTA,
  TYPE__ECHO,
  MAX_AIRCRAFT_TYPES,
};

/** @brief Enumerate different aircraft operational modes. */
enum AircraftMode {
  MODE__IDLE,
  MODE__WAITING_TO_CHARGE,
  MODE__CHARGE_COMPLETE,
  MODE__CHARGING,
  MODE__FLYING,
  MAX_AIRCRAFT_MODES,
};

/*****************************************************************
 * Globals
 *****************************************************************/

/** @brief Stringified AircraftType enum. */
extern const char *aircraft_type_str[];

/** @brief Stringified AircraftMode enum. */
extern const char *aircraft_mode_str[];

/*****************************************************************
 * Class definitions
 *****************************************************************/

/**
 * @class Aircraft
 * @brief Stores characteristics and simulation parameters for an aircraft.
 *
 * This is the base class; each of the specified aircraft types inherits from
 * this one, and updates the aircraft characterization vars accordingly.
 *
 * Lots of things public because there's tight coupling between this class
 * and Simulator class for reporting purposes. Getters/setters would provide
 * better encapsulation but didn't want to write 10000 of them. So they are just
 * public.
 */
class Aircraft {
public:
  // Aircraft characterization (given) -------------------------------------
  AircraftType m_type;
  int m_cruise_speed;         /** Cruise speed (mph) */
  int m_max_battery_cap;      /** Battery capacity (kWh) */
  double m_charge_time;       /** Time to charge (hours) */
  double m_energy_use_cruise; /** Energy use at cruise (kWh/mile) */
  int m_max_passenger_cnt;    /** Maximum passenger count */
  double m_p_fault_hourly;    /** Probability of fault per hour */

  // Aircraft characterization (derived) -----------------------------------
  double m_max_trip_len;    /** Maximum trip distance (miles) */
  double m_charge_per_hour; /** kWh gained per hour of charging */

  // General simulation parameters -----------------------------------------
  AircraftMode m_sim_mode;              /** Current aircraft mode */
  int m_mode_ticks[MAX_AIRCRAFT_MODES]; /** Ticks spent per mode */
  double m_sim_total_miles;             /** Total miles flown (entire sim) */
  double m_sim_total_passenger_mi; /** Passenger miles flown (entire sim) */
  int m_sim_total_num_faults;      /** Total faults (entire sim) */
  double m_sim_rem_energy;         /** Remaining battery capacity (kWh) */
  int m_sim_ticks_waiting_chg;     /** Ticks spent waiting to charge (for
                                      FIFO charger allocation) */
  int m_sim_trips_started;         /** Number of trips started */
  int m_sim_charging_sessions;     /** Number of charging sessions */

  // Per-trip simulation parameters ----------------------------------------
  double m_sim_trip_len;           /** Trip length (mi) */
  double m_sim_trip_miles_elapsed; /** Miles traveled on current trip */
  int m_sim_trip_passenger_cnt;    /** Passengers for current trip */

  Aircraft() {
    memset(m_mode_ticks, 0, sizeof(m_mode_ticks));
    m_sim_total_passenger_mi = 0.0;
    m_sim_total_num_faults = 0;
    m_sim_trip_len = 0.0;
    m_sim_trip_passenger_cnt = 0;
    m_sim_mode = MODE__IDLE;
    m_sim_trip_miles_elapsed = 0.0;
    m_sim_ticks_waiting_chg = 0;
    m_sim_trips_started = 0;
    m_sim_total_miles = 0.0;
    m_sim_charging_sessions = 0;
  };

  virtual ~Aircraft() = default;

  /**
   * @class Aircraft
   * @brief Initialize a trip.
   * @param passengers Number of passengers for current trip
   * @param distance Distance (miles) for current trip
   */
  void start_trip(int passengers, double distance);

  /**
   * @class Aircraft
   * @brief Update flight parameters.
   * @param duration_ms The duration for which to update flight parameters.
   */
  void fly(double duration_ms);

  /**
   * @class Aircraft
   * @brief Simulate probability of fault occurring.
   * @param duration_ms The duration for which to calculate the fault
   * probability.
   */
  void roll_for_fault(double duration_ms);

  /**
   * @class Aircraft
   * @brief Charge the aircraft.
   * @param duration_ms The duration for which to charge the aircraft.
   */
  void charge(double duration_ms);

protected:
  /**
   * @class Aircraft
   * @brief Calculate derived parameters from the given per-vehicle-type
   * parameters.
   */
  void calculate_custom_params();
};

/**
 * @class Alpha
 * @brief Characteristics for Alpha type aircraft.
 */
class Alpha : public Aircraft {
public:
  Alpha() {
    m_type = TYPE__ALPHA;
    m_cruise_speed = 120;
    m_max_battery_cap = 320;
    m_charge_time = 0.6;
    m_energy_use_cruise = 1.6;
    m_max_passenger_cnt = 4;
    m_p_fault_hourly = 0.25;
    calculate_custom_params();
  }
};

/**
 * @class Bravo
 * @brief Characteristics for Bravo type aircraft.
 */
class Bravo : public Aircraft {
public:
  Bravo() {
    m_type = TYPE__BRAVO;
    m_cruise_speed = 100;
    m_max_battery_cap = 100;
    m_charge_time = 0.2;
    m_energy_use_cruise = 1.5;
    m_max_passenger_cnt = 5;
    m_p_fault_hourly = 0.10;
    calculate_custom_params();
  }
};

/**
 * @class Charlie
 * @brief Characteristics for Charlie type aircraft.
 */
class Charlie : public Aircraft {
public:
  Charlie() {
    m_type = TYPE__CHARLIE;
    m_cruise_speed = 160;
    m_max_battery_cap = 220;
    m_charge_time = 0.8;
    m_energy_use_cruise = 2.2;
    m_max_passenger_cnt = 3;
    m_p_fault_hourly = 0.05;
    calculate_custom_params();
  }
};

/**
 * @class Delta
 * @brief Characteristics for Delta type aircraft.
 */
class Delta : public Aircraft {
public:
  Delta() {
    m_type = TYPE__DELTA;
    m_cruise_speed = 90;
    m_max_battery_cap = 120;
    m_charge_time = 0.62;
    m_energy_use_cruise = 0.8;
    m_max_passenger_cnt = 2;
    m_p_fault_hourly = 0.22;
    calculate_custom_params();
  }
};

/**
 * @class Echo
 * @brief Characteristics for Echo type aircraft.
 */
class Echo : public Aircraft {
public:
  Echo() {
    m_type = TYPE__ECHO;
    m_cruise_speed = 30;
    m_max_battery_cap = 150;
    m_charge_time = 0.3;
    m_energy_use_cruise = 5.8;
    m_max_passenger_cnt = 2;
    m_p_fault_hourly = 0.61;
    calculate_custom_params();
  }
};

#endif /* AIRCRAFT_H */
