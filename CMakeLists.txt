cmake_minimum_required(VERSION 3.12)

project(horizongui VERSION 1.0.0)

add_subdirectory(deps/glfw)
add_subdirectory(deps/freetype)

file(GLOB_RECURSE HEADER_FILES include/hgui/*.h)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.c deps/glad/src/glad.c)

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw/include/GLFW ${CMAKE_CURRENT_SOURCE_DIR}/include/GLFW
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/deps/glm/glm ${CMAKE_CURRENT_SOURCE_DIR}/include/glm
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/include/glad ${CMAKE_CURRENT_SOURCE_DIR}/include/glad
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/include/KHR ${CMAKE_CURRENT_SOURCE_DIR}/include/KHR
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/deps/stb/stb_image.h ${CMAKE_CURRENT_SOURCE_DIR}/include/stb/
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/deps/stb/stb_image_write.h ${CMAKE_CURRENT_SOURCE_DIR}/include/stb/
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype/include/ft2build.h ${CMAKE_CURRENT_SOURCE_DIR}/include/
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype/include/freetype ${CMAKE_CURRENT_SOURCE_DIR}/include/freetype
    COMMENT "Moving include files"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/deps/freetype/Debug/freetyped.lib ${CMAKE_CURRENT_SOURCE_DIR}/bin/freetyped.lib
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/deps/glfw/src/Debug/glfw3.lib ${CMAKE_CURRENT_SOURCE_DIR}/bin/glfw3.lib
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/Debug/horizongui.lib ${CMAKE_CURRENT_SOURCE_DIR}/bin/horizongui.lib
    COMMENT "Moving .lib files"
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE )