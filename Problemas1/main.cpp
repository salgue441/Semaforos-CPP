/**
 * @file main.cpp
 * @author Carlos Salguero
 * @brief This is the main file of the project
 * @version 0.1
 * @date 2023-04-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <chrono>
#include <iomanip>

// Project files
#include "monte_carlo.cpp"
#include "pizza.cpp"

// Main function
/**
 * @brief
 * Main function of the project
 * @return int - Status of the program
 */
int main()
{
    MonteCarlo mc;

    auto start = std::chrono::high_resolution_clock::now();
    mc.start();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Time taken by function: "
              << duration.count() / 1000000.0 << " seconds" << std::endl;

    std::cout << "Pi = " << std::setprecision(16)
              << mc.estimate_pi() << std::endl;

    PizzaParty pizzaParty;
}
