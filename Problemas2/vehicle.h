/**
 * @file vehicle.h
 * @author Carlos Salguero
 * @brief Declaration of Vehicle class
 * @version 0.1
 * @date 2023-04-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef VEHICLE_H
#define VEHICLE_H

#include <thread>
#include <atomic>
#include <future>
#include <memory>

// Project files
#include "bridge.h"

class Vehicle
{
public:
    // Constructor
    Vehicle() = default;

    // Destructor
    ~Vehicle() = default;

    // Access Methods
    std::shared_ptr<Bridge> get_bridge() const;
    bool get_direction() const;

    // Mutators
    void set_bridge(std::shared_ptr<Bridge> bridge);
    void set_direction(bool direction);

    // Functions

private:
    std::shared_ptr<Bridge> bridge{};
    std::promise<void> promise{};
    std::future<void> future{};
    std::thread thread{};
    bool direction{};

    // Methods
    void run();
    void wait();
    void one_vehicle();
};

#endif //! VEHICLE_H