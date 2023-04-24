/**
 * @file monte_carlo.cpp
 * @author Carlos Salguero
 * @brief This is the implementation of the Monte Carlo class
 * @version 0.1
 * @date 2023-04-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "monte_carlo.h"

// Access Methods
/**
 * @brief
 * Get the number of points inside the circle
 * @return std::uint32_t - Number of points inside the circle
 */
std::uint32_t MonteCarlo::get_int_circle() const
{
    return m_int_circle;
}

/**
 * @brief
 * Get the total number of points
 * @return std::uint32_t - Total number of points
 */
std::uint32_t MonteCarlo::get_total_points() const
{
    return m_total_points;
}

/**
 * @brief
 * Get the status of the Monte Carlo simulation
 * @return bool - Status of the Monte Carlo simulation
 */
bool MonteCarlo::get_running() const
{
    return m_is_running;
}

// Functions (private)
/**
 * @brief
 * Counts the number of points within a quarter circle
 * @param points Vector of points
 * @return Number of points within a quarter circle
 */
std::uint32_t MonteCarlo::count_points_in_quarter_circle(
    const std::vector<double> &points)
{
    std::uint32_t count{};

    for (std::uint32_t i{}; i < points.size(); i += 2)
    {
        if (points[i] * points[i] + points[i + 1] * points[i + 1] <= 1)
            ++count;
    }

    return count;
}

/**
 * @brief
 * Runs the Monte Carlo simulation to
 * @param num_threads Number of threads to run
 * @param num_samples Number of samples to run
 */
void MonteCarlo::run_thread(
    std::uint32_t num_threads, std::uint32_t num_samples)
{
    m_int_circle = 0;
    m_total_points = 0;
    m_is_running = true;

    m_promises.resize(num_threads);
    m_futures.resize(num_threads);

    for (std::uint32_t i{}; i < num_threads; ++i)
    {
        m_promises[i] = std::promise<std::uint32_t>();
        m_futures[i] = m_promises[i].get_future();
    }

    m_engines.resize(num_threads);
    for (std::uint32_t i{}; i < num_threads; ++i)
        m_engines[i] = std::mt19937(m_rng());

    // Creating threads
    m_threads.resize(num_threads);
    auto num_samples_per_thread{num_samples / num_threads};
    auto remaining_samples{num_samples % num_threads};

    for (std::uint32_t i{}; i < num_threads; ++i)
    {
        auto thread_samples = num_samples_per_thread;

        if (i == num_threads - 1)
            thread_samples += remaining_samples;

        m_threads[i] = std::thread(&MonteCarlo::run_thread_helper,
                                   this, i, thread_samples);
    }

    // Wait for all threads to finish and get the results
    for (std::uint32_t i{}; i < num_threads; ++i)
    {
        auto thread_int_circle = m_futures[i].get();
        m_int_circle += thread_int_circle;
        m_total_points += num_samples_per_thread;

        if (i == 0)
            m_total_points += remaining_samples;

        m_threads[i].join();
    }

    // Clean up
    m_threads.clear();
    m_engines.clear();
    m_promises.clear();
    m_futures.clear();

    m_is_running = false;
}

/**
 * @brief
 * Helper function to run the Monte Carlo simulation
 * @param num_threads Number of threads to run
 * @param num_samples Number of samples to run
 */
void MonteCarlo::run_thread_helper(
    std::uint32_t thread_id, std::uint32_t num_samples)
{
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    std::mt19937 engine(m_rng());
    std::vector<double> points(num_samples * 2);
    std::uint32_t int_circle{};

    for (std::uint32_t i{}; i < num_samples * 2; i += 2)
    {
        auto x{dist(engine)};
        auto y{dist(engine)};

        points[i] = x;
        points[i + 1] = y;

        if (x <= sqrt(1.0 - y * y))
            ++int_circle;
    }

    m_promises[thread_id].set_value(
        count_points_in_quarter_circle(points));
}

// Functions (public)
/**
 * @brief
 * Starts the Monte Carlo simulation
 */
void MonteCarlo::start()
{
    const std::uint32_t num_samples{static_cast<int>(1e8)};
    const std::uint32_t num_threads{std::thread::hardware_concurrency()};

    run_thread(num_threads, num_samples);
    m_is_running = false;
}

/**
 * @brief
 * Estimates the value of pi
 * @return double - Estimated value of pi
 * @return 0.0 - If the simulation is running
 */
double MonteCarlo::estimate_pi() const
{
    if (m_is_running)
        return 0.0;

    return 4.0 * m_int_circle / m_total_points;
}