add_library(
	${RENDERER_VAR}
	STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/Renderer.cpp
)

target_include_directories(
	${RENDERER_VAR}
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/external/glad
	${CMAKE_SOURCE_DIR}/external/glfw/include
)