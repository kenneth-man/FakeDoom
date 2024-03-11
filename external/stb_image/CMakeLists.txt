add_library(
	${STB_IMAGE_VAR}
	STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/stb_image.cpp
)

target_include_directories(
	${STB_IMAGE_VAR}
	PUBLIC
	${CMAKE_SOURCE_DIR}/external/stb_image
)