add_library(${GLAD_KHR_VAR} INTERFACE)

target_include_directories(
	${GLAD_KHR_VAR}
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
)