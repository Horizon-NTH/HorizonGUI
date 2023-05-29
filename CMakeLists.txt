cmake_minimum_required(VERSION 3.12)

project(horizongui VERSION 1.0.0)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/freetype)

file(GLOB_RECURSE HEADER_FILES include/hgui/header/*.h include/hgui/HorizonGUI.h)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.c)

set(EXTERNAL_LIBRARIES 
    ${CMAKE_CURRENT_LIST_DIR}/bin/glfw3.lib
    ${CMAKE_CURRENT_LIST_DIR}/bin/freetyped.lib
    opengl32
)

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:${PROJECT_NAME}>
        ${CMAKE_CURRENT_LIST_DIR}/bin/$<TARGET_FILE_NAME:${PROJECT_NAME}>
)

add_custom_target(CopyLibFilesHGUI ALL
    DEPENDS ${PROJECT_NAME}
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE include include/hgui/external-dependencies)
target_link_libraries(${PROJECT_NAME} PRIVATE ${EXTERNAL_LIBRARIES})