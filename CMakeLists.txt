cmake_minimum_required(VERSION 3.12)

option(API_TYPE "Choose the API type: ON => STATIC, OFF => DYNAMIC" OFF)

project(horizongui VERSION 2.0.0)

if(API_TYPE)
    set(type STATIC)
	file(READ ${CMAKE_CURRENT_SOURCE_DIR}/deps/dhgui/header/Include.h FILE_CONTENTS)
	string(REPLACE "HGUI_DYNAMIC" "HGUI_STATIC" FILE_CONTENTS "${FILE_CONTENTS}")
	file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/deps/dhgui/header/Include.h "${FILE_CONTENTS}")
else(API_TYPE)
    set(type DYNAMIC)
	file(READ ${CMAKE_CURRENT_SOURCE_DIR}/deps/dhgui/header/Include.h FILE_CONTENTS)
	string(REPLACE "HGUI_STATIC" "HGUI_DYNAMIC" FILE_CONTENTS "${FILE_CONTENTS}")
	file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/deps/dhgui/header/Include.h "${FILE_CONTENTS}")
endif(API_TYPE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype)

file(GLOB_RECURSE HEADER_FILES include/hgui/*.h include/hgui/*.hpp)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.c deps/glad/src/glad.c)

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

if(UNIX)
	add_custom_target(UNIX_PRE_BUILD 
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw/include/GLFW ${CMAKE_CURRENT_SOURCE_DIR}/include/GLFW
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/deps/glm/glm ${CMAKE_CURRENT_SOURCE_DIR}/include/glm
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/include/glad ${CMAKE_CURRENT_SOURCE_DIR}/include/glad
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/include/KHR ${CMAKE_CURRENT_SOURCE_DIR}/include/KHR
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/deps/stb/stb_image.h ${CMAKE_CURRENT_SOURCE_DIR}/include/stb/stb_image.h
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/deps/stb/stb_image_write.h ${CMAKE_CURRENT_SOURCE_DIR}/include/stb/stb_image_write.h
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype/include/ft2build.h ${CMAKE_CURRENT_SOURCE_DIR}/include/ft2build.h
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype/include/freetype ${CMAKE_CURRENT_SOURCE_DIR}/include/freetype
		COMMENT "Builing with API type: ${type}"
	)
	add_dependencies(${PROJECT_NAME} UNIX_PRE_BUILD)
else()
	add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw/include/GLFW ${CMAKE_CURRENT_SOURCE_DIR}/include/GLFW
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/deps/glm/glm ${CMAKE_CURRENT_SOURCE_DIR}/include/glm
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/include/glad ${CMAKE_CURRENT_SOURCE_DIR}/include/glad
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/include/KHR ${CMAKE_CURRENT_SOURCE_DIR}/include/KHR
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/deps/stb/stb_image.h ${CMAKE_CURRENT_SOURCE_DIR}/include/stb/stb_image.h
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/deps/stb/stb_image_write.h ${CMAKE_CURRENT_SOURCE_DIR}/include/stb/stb_image_write.h
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype/include/ft2build.h ${CMAKE_CURRENT_SOURCE_DIR}/include/ft2build.h
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype/include/freetype ${CMAKE_CURRENT_SOURCE_DIR}/include/freetype
		COMMENT "Builing with API type: ${type}"
	)

	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/deps/freetype/Debug/freetyped.lib ${CMAKE_CURRENT_SOURCE_DIR}/bin/freetyped.lib
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/deps/glfw/src/Debug/glfw3.lib ${CMAKE_CURRENT_SOURCE_DIR}/bin/glfw3.lib
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/Debug/horizongui.lib ${CMAKE_CURRENT_SOURCE_DIR}/bin/horizongui.lib
		COMMENT "Moving .lib files"
	)
endif()

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw freetype)
