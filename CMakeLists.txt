cmake_minimum_required(VERSION 3.12+)
cmake_policy(SET CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

project(horizongui VERSION 4.0)

set(LIBTYPE STATIC)
set(ALSOFT_UTILS OFF)
set(ALSOFT_NO_CONFIG_UTIL ON)
set(ALSOFT_EXAMPLES OFF)
set(ALSOFT_EAX OFF)
set(ALSOFT_BACKEND_WINMM OFF)
set(BUILD_PROGRAMS OFF)
set(BUILD_EXAMPLES OFF)
set(BUILD_TESTING OFF)
set(ENABLE_EXTERNAL_LIBS OFF)
set(ENABLE_MPEG OFF)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/libsndfile)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/openal-soft)

set(HEADER_FILES
	include/hgui/header/AnimatedSprite.h
	include/hgui/header/Audio.h
	include/hgui/header/Buffer.h
	include/hgui/header/BufferManager.h
	include/hgui/header/Button.h
	include/hgui/header/ButtonManager.h
	include/hgui/header/Canvas.h
	include/hgui/header/CanvasManager.h
	include/hgui/header/Circle.h
	include/hgui/header/Coordinate.hpp
	include/hgui/header/Cursor.h
	include/hgui/header/CursorManager.h
	include/hgui/header/Define.h
	include/hgui/header/Drawer.h
	include/hgui/header/Font.h
	include/hgui/header/FontManager.h
	include/hgui/header/FrameBuffer.h
	include/hgui/header/Function.h
	include/hgui/header/GIF.h
	include/hgui/header/GLSL.h
	include/hgui/header/Image.h
	include/hgui/header/Include.h
	include/hgui/header/Iterator.hpp
	include/hgui/header/KeyBoardManager.h
	include/hgui/header/Label.h
	include/hgui/header/LabelManager.h
	include/hgui/header/Maths.hpp
	include/hgui/header/Monitor.h
	include/hgui/header/MonitorManager.h
	include/hgui/header/MouseManager.h
	include/hgui/header/Rectangle.h
	include/hgui/header/RenderBuffer.h
	include/hgui/header/Renderer.h
	include/hgui/header/Shader.h
	include/hgui/header/ShaderManager.h
	include/hgui/header/Shape.h
	include/hgui/header/Slider.h
	include/hgui/header/SliderManager.h
	include/hgui/header/SoundPlayer.h
	include/hgui/header/SoundPlayerManager.h
	include/hgui/header/Sprite.h
	include/hgui/header/SpriteManager.h
	include/hgui/header/StraightLine.h
	include/hgui/header/TagManager.h
	include/hgui/header/TaskManager.h
	include/hgui/header/Texture.h
	include/hgui/header/TextureManager.h
	include/hgui/header/Timer.h
	include/hgui/header/Tools.h
	include/hgui/header/Triangle.h
	include/hgui/header/Vector.hpp
	include/hgui/header/VertexArrayObject.h
	include/hgui/header/VertexBufferObject.h
	include/hgui/header/Widget.h
	include/hgui/header/Window.h
	include/hgui/header/WindowManager.h
	include/hgui/HorizonGUI.h
	include/hgui/header/TextInput.h
	include/hgui/header/TextInputManager.h
)

set(SOURCE_FILES
	src/stbi.cpp
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
	deps/glad/src/glad.c
	src/TextInput.cpp
	src/TextInputManager.cpp
)

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
		ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/$<CONFIG>"
		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/$<CONFIG>"
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/$<CONFIG>"
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