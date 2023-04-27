cmake_minimum_required(VERSION 3.20)

# Cpp standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project name
project(Semaforo)

# Add executable
add_executable(Semaforo main.cpp)

# Add include directories
target_link_directories(Semaforo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(Semaforo PUBLIC -Wall -Wextra -Werror)