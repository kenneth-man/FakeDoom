add_library(
	${TEXTURE_VAR}
	STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/Texture.cpp
)

target_include_directories(
	${TEXTURE_VAR}
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/external/glad
	${CMAKE_SOURCE_DIR}/external/glfw/include
	${CMAKE_SOURCE_DIR}/external/stb_image
)