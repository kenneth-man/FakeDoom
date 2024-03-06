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
set(VERTEX_BUFFER_VAR vertex_buffer)
set(VERTEX_BUFFER_LAYOUT_VAR vertex_buffer_layout)
set(INDEX_BUFFER_VAR index_buffer)
set(VERTEX_ARRAY_VAR vertex_array)
set(SHADER_VAR shader)
set(RENDERER_VAR renderer)

# Adds a subdirectory to the build; must contain CMakeLists.txt file
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/glfw)
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
	${VERTEX_BUFFER_VAR}
	${VERTEX_BUFFER_LAYOUT_VAR}
	${INDEX_BUFFER_VAR}
	${VERTEX_ARRAY_VAR}
	${SHADER_VAR}
	${RENDERER_VAR}
)