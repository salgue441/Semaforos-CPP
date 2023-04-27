/**
 * @file vehicle.cpp
 * @author Carlos Salguero
 * @brief Implementation of the class Vehicle
 * @version 0.1
 * @date 2023-04-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "vehicle.h"

/**
 * @brief
 * Construct a new Vehicle:: Vehicle object
 * @param direction Direction of the vehicle
 */
Vehicle::Vehicle(Direction direction) noexcept
    : direction(direction), m_vehicles_on_bridge(0), m_vehicles_waiting(0)
{
}

// Access Methods
/**
 * @brief
 * Get the direction of the vehicle
 * @return Direction Direction of the vehicle
 */
Direction Vehicle::get_direction() const
{
    return direction;
}

// Mutators
/**
 * @brief
 * Set the direction of the vehicle
 * @param direction Direction of the vehicle
 */
void Vehicle::set_direction(Direction direction)
{
    this->direction = direction;
}

// Functions (Private)
/**
 * @brief
 * Function to simulate the arrival of a vehicle to the bridge from the North
 */
void Vehicle::cross_bridge_north()
{
    std::cout << "Vehicle " << std::this_thread::get_id()
              << " is crossing the bridge from North to South" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Vehicle " << std::this_thread::get_id()
              << " has crossed the bridge from North to South" << std::endl;
}

/**
 * @brief
 * Function to simulate the arrival of a vehicle to the bridge from the South
 */
void Vehicle::cross_bridge_south()
{
    std::cout << "Vehicle " << std::this_thread::get_id()
              << " is crossing the bridge from South to North" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Vehicle " << std::this_thread::get_id()
              << " has crossed the bridge from South to North" << std::endl;
}

// Functions (Public)
/**
 * @brief
 * Function to simulate the arrival of a vehicle to the bridge
 * @param direction Direction of the vehicle
 */
void Vehicle::arrive_bridge(Direction vehicle_direction)
{
    std::unique_lock<std::mutex> lock(m_mutex);

    m_cv.wait(lock, [this, vehicle_direction]()
              { return m_vehicles_on_bridge == 0 && (vehicle_direction == Direction::NORTH ? m_vehicles_waiting.load() == 0 : m_vehicles_waiting.load() == 0); });

    m_vehicles_waiting.fetch_add(1);
    std::cout << "Vehicle " << std::this_thread::get_id()
              << " has arrived to the bridge" << std::endl;

    m_cv.wait(lock, [this, vehicle_direction]()
              { return (vehicle_direction == Direction::NORTH && m_vehicles_on_bridge < 3 && m_vehicles_waiting.load() == 1) ||
                       (vehicle_direction == Direction::SOUTH && m_vehicles_on_bridge < 3 && m_vehicles_waiting.load() == 1); });

    m_vehicles_waiting.fetch_sub(1);
    m_vehicles_on_bridge++;
}

/**
 * @brief
 * Function to simulate the crossing of a vehicle through the bridge
 * @param direction Direction of the vehicle
 */
void Vehicle::cross_bridge(Direction vehicle_direction)
{
    if (vehicle_direction == Direction::NORTH)
    {
        cross_bridge_north();
    }
    else
    {
        cross_bridge_south();
    }
}

/**
 * @brief
 * Function to simulate the exit of a vehicle from the bridge
 * @param direction Direction of the vehicle
 */
void Vehicle::exit_bridge()
{
    std::unique_lock<std::mutex> lock(m_mutex);

    m_vehicles_on_bridge--;

    std::cout << "Vehicle " << std::this_thread::get_id()
              << " has exited the bridge" << std::endl;

    m_cv.notify_all();
}