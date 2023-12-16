# Vertex
file(GLOB_RECURSE GLSL_VERTEX_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/vertex/*.glsl)
foreach(SHADER_FILE ${GLSL_VERTEX_SOURCES})
    file(STRINGS ${SHADER_FILE} SHADER_CONTENT)
    get_filename_component(FILE_NAME ${SHADER_FILE} NAME_WE)
    string(TOUPPER "${FILE_NAME}" FILE_NAME)
    string(JOIN "\\n" SHADER_CONTENT ${SHADER_CONTENT})
    set(VERTEX_${FILE_NAME} ${SHADER_CONTENT})
endforeach()

# Fragment
file(GLOB_RECURSE GLSL_FRAGMENT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/fragment/*.glsl)
foreach(SHADER_FILE ${GLSL_FRAGMENT_SOURCES})
    file(STRINGS ${SHADER_FILE} SHADER_CONTENT)
    get_filename_component(FILE_NAME ${SHADER_FILE} NAME_WE)
    string(TOUPPER "${FILE_NAME}" FILE_NAME)
    string(JOIN "\\n" SHADER_CONTENT ${SHADER_CONTENT})
    set(FRAGMENT_${FILE_NAME} ${SHADER_CONTENT})
endforeach()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/GLSL.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/hgui/header/GLSL.h @ONLY)