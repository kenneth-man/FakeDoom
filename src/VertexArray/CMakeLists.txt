add_library(
	${VERTEX_ARRAY_VAR}
	STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/VertexArray.cpp
)

target_include_directories(
	${VERTEX_ARRAY_VAR}
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/src/VertexBuffer
	${CMAKE_SOURCE_DIR}/src/VertexBufferLayout
	${CMAKE_SOURCE_DIR}/external/glad
	${CMAKE_SOURCE_DIR}/external/glfw/include
)