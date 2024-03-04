add_library(
	${SHADER_VAR}
	STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/Shader.cpp
)

target_include_directories(
	${SHADER_VAR}
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/src/utils/functions
	${CMAKE_SOURCE_DIR}/external/glad
	${CMAKE_SOURCE_DIR}/external/glfw/include
)