#!/bin/bash

# Create/update build files, compile and create/update executables in debug mode
cd ..
cd build
cmake .. -DGLFW_BUILD_DOCS=OFF -G "Visual Studio 17 2022"
cmake --build .

$SHELL