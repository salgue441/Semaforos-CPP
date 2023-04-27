/**
 * @file main.cpp
 * @author Carlos Salguero
 * @brief Main file of the program
 * @version 0.1
 * @date 2023-04-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <memory>
#include <future>

#include "vehicle.cpp"

int main()
{
    std::vector<std::shared_ptr<Vehicle>> vehicles;

    // Create vehicles
    for (int i = 0; i < 6; ++i)
    {
        Direction direction = (i < 3) ? Direction::NORTH : Direction::SOUTH;
        vehicles.push_back(std::make_shared<Vehicle>(direction));
    }

    // Start vehicle threads
    std::vector<std::thread> threads;
    for (const auto &vehicle : vehicles)
    {
        threads.emplace_back([vehicle]()
                             {
            vehicle->arrive_bridge(vehicle->get_direction());
            vehicle->cross_bridge(vehicle->get_direction());
            vehicle->exit_bridge(); });
    }

    // Wait for all threads to finish
    for (auto &thread : threads)
    {
        thread.join();
    }
}
