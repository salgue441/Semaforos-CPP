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

#include <random>             // std::mt19937, std::uniform_real_distribution,
#include <vector>             // std::vector
#include <thread>             // std::thread
#include <future>             // std::promise, std::future
#include <cstdint>            // std::uint32_t
#include <algorithm>          // std::for_each
#include <atomic>             // std::atomic
#include <condition_variable> // std::condition_variable

class PizzaParty
{
public:
    // Constructor
    PizzaParty() = default;

    // Destructor
    ~PizzaParty() = default;

    // Access Methods
    std::uint32_t get_num_students() const;
    std::uint32_t get_num_slices_per_pizza() const;
    std::uint32_t get_num_pizzas() const;
    bool get_pizzeria_open() const;
    bool get_pizza_available() const;

    // Mutator Methods
    void set_num_students(std::uint32_t);
    void set_num_slices_per_pizza(std::uint32_t);
    void set_num_pizzas(std::uint32_t);
    void set_pizzeria_open(bool);

    // Functions
    void start_party();

private:
    std::uint32_t m_num_students{};
    std::uint32_t m_num_slices_per_pizza{};
    std::uint32_t m_num_pizzas{};
    std::atomic<bool> m_pizzeria_open{false};
    std::atomic<bool> m_pizza_available{false};
    std::vector<std::thread> m_students{};
    std::thread m_pizzeria_thread{};
    std::thread delivery_thread{};
    std::condition_variable m_cv_pizza_available{};
    std::condition_variable m_cv_pizza_consumed{};

    // Functions
    void student(std::uint32_t);
    void delivery();
    void pizzeria();
};

#endif //! PIZZA_H