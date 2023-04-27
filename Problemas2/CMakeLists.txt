cmake_minimum_required(VERSION 3.20)

# Cpp standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project name
project(Puente)

# Add executable
add_executable(Puente main.cpp)

# Add include directories
target_link_directories(Puente PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(Puente PUBLIC -Wall -Wextra -Werror)