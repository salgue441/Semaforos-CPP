#!/bin/zsh

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

# Clean up
make clean 
cd ..