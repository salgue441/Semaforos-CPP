/**
 * @file pizza.h
 * @author Carlos Salguero
 * @author Sergio Garnica
 * @brief Definition of the pizza class
 * @version 0.1
 * @date 2023-04-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef PIZZA_H
#define PIZZA_H

#include <random>    // std::mt19937, std::uniform_real_distribution,
#include <vector>    // std::vector
#include <thread>    // std::thread
#include <future>    // std::promise, std::future
#include <cstdint>   // std::uint32_t
#include <algorithm> // std::for_each

class PizzaParty
{
public:
    // Constructor
    PizzaParty() = default;

    // Destructor
    ~PizzaParty() = default;

private:
    std::uint32_t m_num_students{};
    std::uint32_t m_num_slices_per_pizza{};
    std::uint32_t m_num_pizzas{};
    std::atomic<bool> m_pizzeria_open{false};
    std::atomic<bool> m_pizza_available{false};
    std::vector<std::thread> m_students{};
    std::thread delivery_thread{};
    std::condition_variable m_cv_pizza_available{};
    std::condition_variable m_cv_pizza_consumed{};

    // Functions
    void student(std::uint32_t);
    void delivery();
};

#endif //! PIZZA_H