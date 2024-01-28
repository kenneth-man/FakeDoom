# Default cmake version
cmake_minimum_required(VERSION 3.26.3)

# Project name
project(FakeDoom)

# Create executable for 'main.cpp'
add_executable(${PROJECT_NAME} main.cpp)

# Useless???
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Without this line, CMake will not actually use C++17, meaning that the above 3 lines don't seem to be doing anything; Not sure why
target_compile_features(
	${PROJECT_NAME}
	PRIVATE
	cxx_std_17
)

# Adds a subdirectory to the build
add_subdirectory(external/glfw)

# Specifies include directories to use when compiling a given target
target_include_directories(
	${PROJECT_NAME}
	PUBLIC
	external/glfw/include
)

# Specifies the paths in which the linker should search for libraries when linking a given target.
target_link_directories(
	${PROJECT_NAME}
	PRIVATE
	external/glfw/src
)

# Specify libraries or flags to use when linking a given target and/or its dependents
target_link_libraries(
	${PROJECT_NAME}
	glfw
)