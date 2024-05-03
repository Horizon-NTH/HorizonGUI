cmake_minimum_required(VERSION 3.15+)

if (NOT DEFINED SKBUILD_PROJECT_NAME)
	set(SKBUILD_PROJECT_NAME hgui)
endif ()

if (NOT DEFINED SKBUILD_PROJECT_VERSION)
	set(SKBUILD_PROJECT_VERSION 3.0)
endif ()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(${SKBUILD_PROJECT_NAME} LANGUAGES CXX VERSION ${SKBUILD_PROJECT_VERSION})

set(PYBIND11_NEWPYTHON ON)
add_subdirectory(../deps/pybind11 ${CMAKE_CURRENT_BINARY_DIR}/deps/pybind11)
add_subdirectory(.. ${CMAKE_CURRENT_BINARY_DIR}/deps/horizongui)

set(HEADER_FILES
	include/Include.h
	include/fwd.h
	include/opaque.h
	include/PyCoordinate.h
	include/PyShape.h
	include/PyWidgets.h
)

set(SOURCE_FILES
	src/hgui.cpp
	src/PyVector.cpp
	src/PyFunction.cpp
	src/PyCoordinate.cpp
	src/PyShape.cpp
	src/PyEnum.cpp
	src/PyData.cpp
	src/PyResources.cpp
	src/PyUtils.cpp
	src/PyManager.cpp
	src/PyWidgets.cpp
)

pybind11_add_module(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE ../deps/pybind11/include ../include)
target_link_libraries(${PROJECT_NAME} PRIVATE horizongui glfw freetype OpenAL sndfile)

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION .)