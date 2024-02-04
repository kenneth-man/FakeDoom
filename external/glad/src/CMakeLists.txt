add_library(
	${GLAD_LIB_VAR}
	STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/glad.c
)

target_include_directories(
	${GLAD_LIB_VAR}
	PUBLIC
	${CMAKE_SOURCE_DIR}/external/glad
)