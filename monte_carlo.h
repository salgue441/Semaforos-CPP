/**
 * @file monte_carlo.h
 * @author Carlos Salguero
 * @brief This is the definition of the Monte Carlo class
 * @version 0.1
 * @date 2023-04-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

// C++ libraries
#include <random>
#include <vector>
#include <thread>
#include <algorithm>
#include <future>
#include <cstdint>

/**
 * @brief
 * Class that implements the Monte Carlo method
 * to calculate the value of pi
 */
class MonteCarlo
{
public:
    // Constructor
    MonteCarlo() = default;

    // Destructor
    ~MonteCarlo() = default;

    // Access Methods
    std::uint32_t get_int_circle() const;
    std::uint32_t get_total_points() const;
    bool get_running() const;

    // Functions
    void start();
    double estimate_pi() const;

private:
    std::mt19937 m_rng{};
    std::vector<std::thread> m_threads{};
    std::vector<std::mt19937> m_engines{};
    std::vector<std::promise<std::uint32_t>> m_promises{};
    std::vector<std::future<std::uint32_t>> m_futures{};
    std::atomic<std::uint32_t> m_int_circle{};
    std::atomic<std::uint32_t> m_total_points{};
    std::atomic<bool> m_is_running{false};

    // Private methods
    std::uint32_t count_points_in_quarter_circle(const std::vector<double> &);
    void run_thread(std::uint32_t, std::uint32_t);
    void run_thread_helper(std::uint32_t, std::uint32_t);
};

#endif //! MONTE_CARLO_H