#!/bin/bash

# Remove all build files, Create build files, compile and create executables in release mode
cd ..
rm -rf build
mkdir build
cd build
cmake .. -DGLFW_BUILD_DOCS=OFF
cmake --build . --config Release