add_library(
	${GLAD_H_VAR}
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/glad.h
)

target_include_directories(
	${GLAD_H_VAR}
	INTERFACE
	${CMAKE_SOURCE_DIR}/external/glad
)