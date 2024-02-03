add_library(
	${FUNCTIONS_VAR}
	STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/functions.cpp
)

target_include_directories(
	${FUNCTIONS_VAR}
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)