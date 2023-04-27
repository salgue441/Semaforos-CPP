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
./Puente

# Clean up
make clean 
cd ..