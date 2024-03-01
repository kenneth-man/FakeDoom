add_library(
	${INDEX_BUFFER_VAR}
	STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/IndexBuffer.cpp
)

target_include_directories(
	${INDEX_BUFFER_VAR}
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/external/glad
	${CMAKE_SOURCE_DIR}/external/glfw/include
)