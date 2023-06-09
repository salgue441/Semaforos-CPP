#!bin/bash

if [ ! -d "build" ]; then
    mkdir build
fi

# Configure build with CMake
cd build
cmake ..

# Build the project
make

# Run the project
./Semaforo

# Clean Up
make clean
cd ..

# Compiling pizza.cpp
g++ -std=c++2a pizza.cpp -o pizza
./pizza

rm pizza
