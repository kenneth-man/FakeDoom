#!/bin/bash

# Remove all build files, Create build files, compile and create executables in debug mode
cd ..
rm -rf build
mkdir build
cd build
cmake .. -DGLFW_BUILD_DOCS=OFF
cmake --build .

# prevent WSL terminal automatically closing if run in vscode
$SHELL