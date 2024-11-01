cmake_minimum_required(VERSION 3.12+)
cmake_policy(SET CMP0077 NEW)
cmake_policy(SET CMP0148 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0148 NEW)

if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan_provider.cmake")
	message(STATUS "Downloading conan_provider.cmake from Conan repository")
	file(DOWNLOAD
		"https://raw.githubusercontent.com/conan-io/cmake-conan/develop2/conan_provider.cmake"
		${CMAKE_BINARY_DIR}/conan_provider.cmake)
endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CONAN_BUILD_PROFILE "default;auto-cmake")
set(CONAN_HOST_PROFILE "default;auto-cmake")
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif ()
set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES "${CMAKE_BINARY_DIR}/conan_provider.cmake")

project(horizongui VERSION 0.4.0)

set(HEADER_FILES
	include/AnimatedSprite.h
	include/Audio.h
	include/Buffer.h
	include/BufferManager.h
	include/Button.h
	include/ButtonManager.h
	include/Canvas.h
	include/CanvasManager.h
	include/Circle.h
	include/Coordinate.hpp
	include/Cursor.h
	include/CursorManager.h
	include/Define.h
	include/Drawer.h
	include/Font.h
	include/FontManager.h
	include/FrameBuffer.h
	include/Function.h
	include/GIF.h
	include/GLSL.h
	include/Image.h
	include/Iterator.hpp
	include/KeyBoardManager.h
	include/Label.h
	include/LabelManager.h
	include/Maths.hpp
	include/Monitor.h
	include/MonitorManager.h
	include/MouseManager.h
	include/Rectangle.h
	include/RenderBuffer.h
	include/Renderer.h
	include/Shader.h
	include/ShaderManager.h
	include/Shape.h
	include/Slider.h
	include/SliderManager.h
	include/SoundPlayer.h
	include/SoundPlayerManager.h
	include/Sprite.h
	include/SpriteManager.h
	include/StraightLine.h
	include/TagManager.h
	include/TaskManager.h
	include/Texture.h
	include/TextureManager.h
	include/Timer.h
	include/Tools.h
	include/Triangle.h
	include/Vector.hpp
	include/VertexArrayObject.h
	include/VertexBufferObject.h
	include/Widget.h
	include/Window.h
	include/WindowManager.h
	include/TextInput.h
	include/TextInputManager.h
)

set(SOURCE_FILES
	src/AnimatedSprite.cpp
	src/Audio.cpp
	src/Buffer.cpp
	src/BufferManager.cpp
	src/Button.cpp
	src/ButtonManager.cpp
	src/Canvas.cpp
	src/CanvasManager.cpp
	src/Circle.cpp
	src/Cursor.cpp
	src/CursorManager.cpp
	src/Drawer.cpp
	src/Font.cpp
	src/FontManager.cpp
	src/FrameBuffer.cpp
	src/Function.cpp
	src/GIF.cpp
	src/Image.cpp
	src/KeyBoardManager.cpp
	src/Label.cpp
	src/LabelManager.cpp
	src/Monitor.cpp
	src/MonitorManager.cpp
	src/MouseManager.cpp
	src/Rectangle.cpp
	src/RenderBuffer.cpp
	src/Renderer.cpp
	src/Shader.cpp
	src/ShaderManager.cpp
	src/Shape.cpp
	src/Slider.cpp
	src/SliderManager.cpp
	src/SoundPlayer.cpp
	src/SoundPlayerManager.cpp
	src/Sprite.cpp
	src/SpriteManager.cpp
	src/StraightLine.cpp
	src/TagManager.cpp
	src/TaskManager.cpp
	src/Texture.cpp
	src/TextureManager.cpp
	src/Timer.cpp
	src/Tools.cpp
	src/Triangle.cpp
	src/VertexArrayObject.cpp
	src/VertexBufferObject.cpp
	src/Widget.cpp
	src/Window.cpp
	src/WindowManager.cpp
	src/TextInput.cpp
	src/TextInputManager.cpp
)

find_package(glfw3 3.3.8 REQUIRED)
find_package(Freetype 2.13.2 REQUIRED)
find_package(glm 1.0.1 REQUIRED)
find_package(stb REQUIRED)
find_package(glad 0.1.36 REQUIRED)
find_package(OpenAL 1.23.1 REQUIRED)
find_package(SndFile 1.2.2 REQUIRED)
find_package(pybind11 2.13.5 REQUIRED)
set(DEPS pybind11::pybind11 glfw freetype glm::glm stb::stb glad::glad OpenAL::OpenAL SndFile::sndfile)

include(${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/generate_shaders.cmake)

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${DEPS})

install(TARGETS ${PROJECT_NAME} DESTINATION lib)