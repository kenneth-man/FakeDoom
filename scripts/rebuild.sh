#!/bin/bash

# Create/update build files, compile and create/update executables in debug mode
cd ..
cd build
cmake .. -DGLFW_BUILD_DOCS=OFF
cmake --build .