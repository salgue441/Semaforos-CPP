/**
 * @file bridge.h
 * @author Carlos Salguero
 * @brief Declaration of Bridge class
 * @version 0.1
 * @date 2023-04-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef BRIDGE_H
#define BRIDGE_H

#include <thread>
#include <atomic>
#include <future>
#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <semaphore>

class Bridge
{
public:
    // Constructor
    Bridge() = default;

    // Destructor
    ~Bridge() = default;

    // Access Methods
    std::atomic<uint32_t> get_num_vehicles() const;

    // Mutators
    void set_num_vehicles(uint32_t num_vehicles);

    // Functions

private:
    std::atomic<uint32_t> num_vehicles{};
    std::mutex mutex{};
    std::condition_variable cv{};
    std::queue<std::shared_ptr<std::promise<void>>> waiting_vehicles{};
    std::counting_semaphore<3> bridge_capacity;
};

#endif //! BRIDGE_H