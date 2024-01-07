cmake_minimum_required(VERSION 3.12+)

option(API_TYPE "Choose the API type: ON => STATIC, OFF => DYNAMIC" OFF)

project(horizongui VERSION 2.0)

if (API_TYPE)
    set(type STATIC)
    file(READ ${CMAKE_CURRENT_SOURCE_DIR}/include/hgui/header/Include.h FILE_CONTENTS)
    string(REPLACE "HGUI_DYNAMIC" "HGUI_STATIC" FILE_CONTENTS "${FILE_CONTENTS}")
    file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/include/hgui/header/Include.h "${FILE_CONTENTS}")
else (API_TYPE)
    set(type DYNAMIC)
    file(READ ${CMAKE_CURRENT_SOURCE_DIR}/include/hgui/header/Include.h FILE_CONTENTS)
    string(REPLACE "HGUI_STATIC" "HGUI_DYNAMIC" FILE_CONTENTS "${FILE_CONTENTS}")
    file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/include/hgui/header/Include.h "${FILE_CONTENTS}")
endif (API_TYPE)

set(LIBTYPE STATIC)
set(ALSOFT_UTILS OFF)
set(ALSOFT_NO_CONFIG_UTIL ON)
set(ALSOFT_EXAMPLES OFF)
set(ALSOFT_EAX OFF)
set(ALSOFT_BACKEND_WINMM OFF)
set(BUILD_PROGRAMS OFF)
set(BUILD_EXAMPLES OFF)
set(BUILD_TESTING OFF)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/openal-soft)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/libsndfile)

file(GLOB_RECURSE HEADER_FILES include/hgui/*.h include/hgui/*.hpp)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.c deps/glad/src/glad.c)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw/include/GLFW DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/deps/glm/glm DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/include/glad DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/include/KHR DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/deps/stb/stb_image.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/stb)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/deps/stb/stb_image_write.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/stb)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype/include/ft2build.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype/include/freetype DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/deps/openal-soft/include/AL DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/deps/libsndfile/include/sndfile.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/snd)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/deps/libsndfile/include/sndfile.hh DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/snd)

include(${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/generate_shaders.cmake)

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw freetype OpenAL sndfile)

function(set_common_target_properties target_name)
    set_target_properties(${target_name} PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/lib
            ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/lib
    )
    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        set_target_properties(${target_name} PROPERTIES
                COMPILE_OPTIONS "/Z7"
        )
    endif ()
endfunction()

set_common_target_properties(${PROJECT_NAME})
set_common_target_properties(freetype)
set_common_target_properties(glfw)
set_common_target_properties(OpenAL)
set_common_target_properties(sndfile)