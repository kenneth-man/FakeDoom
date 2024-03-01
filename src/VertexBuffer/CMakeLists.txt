add_library(
	${VERTEX_BUFFER_VAR}
	STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/VertexBuffer.cpp
)

target_include_directories(
	${VERTEX_BUFFER_VAR}
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/external/glad
	${CMAKE_SOURCE_DIR}/external/glfw/include
)