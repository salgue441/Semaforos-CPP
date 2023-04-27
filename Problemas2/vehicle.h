/**
 * @file vehicle.h
 * @author Carlos Salguero
 * @brief Definition of the class Vehicle
 * @version 0.1
 * @date 2023-04-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <semaphore>
#include <iostream>
#include <atomic>
#include <mutex>
#include <condition_variable>

#ifndef VEHICLE_H_
#define VEHICLE_H_

/**
 * @brief
 * Enum class to represent the direction of the vehicle
 */
enum class Direction
{
    NORTH,
    SOUTH,
};

/**
 * @brief
 * Class to represent a vehicle
 */
class Vehicle
{
public:
    // Constructor
    Vehicle() = default;
    explicit Vehicle(Direction) noexcept;

    // Destructor
    ~Vehicle() = default;

    // Access Methods
    Direction get_direction() const;

    // Mutators
    void set_direction(Direction);

    // Functions
    void arrive_bridge(Direction);
    void cross_bridge(Direction);
    void exit_bridge();

private:
    Direction direction;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::atomic<std::uint32_t> m_vehicles_on_bridge;
    std::atomic<std::uint32_t> m_vehicles_waiting;

    // Functions
    void cross_bridge_north();
    void cross_bridge_south();
};

#endif //! VEHICLE_H_