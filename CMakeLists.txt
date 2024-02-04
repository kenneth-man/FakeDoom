# Default cmake version
cmake_minimum_required(VERSION 3.26.3)

# Project name
project(FakeDoom)

# Create executable for 'main.cpp'
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

# Use C++17 compiler
target_compile_features(
	${PROJECT_NAME}
	PRIVATE
	cxx_std_17
)

# Variables
set(GLFW_LIB_VAR glfw)
set(GLAD_LIB_VAR glad)
set(GLAD_H_VAR glad_h)
set(GLAD_KHR_VAR glad_khr)
set(FUNCTIONS_VAR functions)

# Adds a subdirectory to the build; must contain CMakeLists.txt file
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/glfw)
# changed the includes in glad.c, glad.h, and khrplatform.h to use relative path;
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/glad)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Allows usage of angle brackets to include libraries `<>`
# Otherwise can just use relative paths with ""
target_include_directories(
	${PROJECT_NAME}
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glad
)

# Specify libraries or flags to use when linking the target and/or its dependents
# Only need to link libraries that have src files (e.g. .cpp)
target_link_libraries(
	${PROJECT_NAME}
	${GLFW_LIB_VAR}
	${GLAD_LIB_VAR}
	${FUNCTIONS_VAR}
)