# FakeDoom

- ### C++
- ### OpenGL (GLFW)
- ### GLAD
- ### Catch2

## Setup
1. ### Install CMake and MSVC C++ Compiler (e.g. Install Visual Studio Community Edition)
2. ### Make sure your system can run bash scripts (e.g. Windows subsystem for Linux is recommended for Windows users)
2. ### In the root directory:
```
git submodule update --init --recursive
cd scripts
.\clean_build_without_exit.sh
.\execute_debug.sh
```