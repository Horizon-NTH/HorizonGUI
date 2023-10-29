#include <hgui/header/Function.h>

#if defined(HGUI_DYNAMIC)
void hgui::init()
{
	static bool alreadyInitialize = false;
	if (!alreadyInitialize)
	{
		kernel::init_glfw();
		MonitorManager::init();
		TagManager::create_tag(HGUI_TAG_MAIN);
		TagManager::set_current_tag(HGUI_TAG_MAIN);
		alreadyInitialize = true;
	}
}

void hgui::end()
{
	glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
}

void hgui::kernel::init_glad()
{
	if (glfwGetCurrentContext())
	{
		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			glfwTerminate();
			throw std::runtime_error("ERROR WITH GLAD LOADING");
		}
#ifdef HGUI_VERSION_DEBUG
		int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(debug, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}
#endif // HGUI_VERSION_DEBUG
	}
	else
	{
		throw std::runtime_error("WINDOW NEEDED TO INITIALIZED GLAD");
	}
}

void hgui::kernel::resources_cleaner()
{
	ButtonManager::m_shader = nullptr;
	ButtonManager::m_cursor = nullptr;
	SpriteManager::m_shader = nullptr;
	LabelManager::m_shader = nullptr;
	CanvasManager::m_shader = nullptr;
	Widget::m_binds.clear();
	Widget::m_bindedTags.clear();
	Widget::m_widgets.clear();
	TagManager::m_tags.clear();
	KeyBoardManager::m_keys.clear();
	MouseManager::m_inputs.clear();
}

void hgui::kernel::debug(const GLenum source, const GLenum type, const unsigned int id, const GLenum severity,
                         GLsizei length, const char* message, const void* userParam)
{
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
		return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:
		std::cout << "Source: API";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		std::cout << "Source: Window System";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		std::cout << "Source: Shader Compiler";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		std::cout << "Source: Third Party";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		std::cout << "Source: Application";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		std::cout << "Source: Other";
		break;
	}
	std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:
		std::cout << "Type: Error";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		std::cout << "Type: Deprecated Behaviour";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		std::cout << "Type: Undefined Behaviour";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		std::cout << "Type: Portability";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		std::cout << "Type: Performance";
		break;
	case GL_DEBUG_TYPE_MARKER:
		std::cout << "Type: Marker";
		break;
	case GL_DEBUG_TYPE_PUSH_GROUP:
		std::cout << "Type: Push Group";
		break;
	case GL_DEBUG_TYPE_POP_GROUP:
		std::cout << "Type: Pop Group";
		break;
	case GL_DEBUG_TYPE_OTHER:
		std::cout << "Type: Other";
		break;
	}
	std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		std::cout << "Severity: high";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		std::cout << "Severity: medium";
		break;
	case GL_DEBUG_SEVERITY_LOW:
		std::cout << "Severity: low";
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		std::cout << "Severity: notification";
		break;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

bool hgui::kernel::init_glfw()
{
	static bool alreadyInitialized = false;
	if (!alreadyInitialized)
	{
		if (!glfwInit())
		{
			glfwTerminate();
			throw std::runtime_error("ERROR WITH GLFW LOADING");
		}
		alreadyInitialized = true;
		return alreadyInitialized;
	}
	else
	{
		throw std::runtime_error("GLFW ALREADY INITIALIZED");
	}
}
#elif defined(HGUI_STATIC)
void hgui::init()
{
	static bool alreadyInitialize = false;
	if (!alreadyInitialize)
	{
		kernel::init_glfw();
		MonitorManager::init();
		TagManager::create_tag(HGUI_TAG_MAIN);
		TagManager::set_current_tag(HGUI_TAG_MAIN);
		CursorManager::init();
		alreadyInitialize = true;
	}
}

void hgui::end()
{
	glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
}

void hgui::kernel::init_glad()
{
	if (glfwGetCurrentContext())
	{
		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			glfwTerminate();
			throw std::runtime_error("ERROR WITH GLAD LOADING");
		}
#ifdef HGUI_VERSION_DEBUG
		int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(debug, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}
#endif // HGUI_VERSION_DEBUG
	}
	else
	{
		throw std::runtime_error("WINDOW NEEDED TO INITIALIZED GLAD");
	}
}

void hgui::kernel::init_resources()
{
	ShaderManager::create(HGUI_SHADER_FRAMEBUFFER,
	                      R"(
			#version 330 core
			layout (location = 0) in vec4 vertex;

			out vec2 texturePosition;

			void main()
			{
				texturePosition = vertex.zw;
				gl_Position = vec4(vertex.xy, 0.0, 1.0);
			}
		)",
	                      R"(
			#version 330 core

			out vec4 fragmentColor;

			in vec2 texturePosition;

			uniform sampler2D screenTexture;
			uniform int type;

			void main()
			{
				if (type == 1)
				{
					const float offset = 1.0 / 300.0;
						vec2 offsets[9] = vec2[](
						vec2(-offset,  offset),
						vec2( 0.0f,    offset),
						vec2( offset,  offset),
						vec2(-offset,  0.0f),
						vec2( 0.0f,    0.0f),
						vec2( offset,  0.0f),
						vec2(-offset, -offset),
						vec2( 0.0f,   -offset),
						vec2( offset, -offset)
					);

					float kernel[9] = float[](
						1.0 / 16, 2.0 / 16, 1.0 / 16,
						2.0 / 16, 4.0 / 16, 2.0 / 16,
						1.0 / 16, 2.0 / 16, 1.0 / 16
					);

					vec3 sampleTex[9];
					for(int i = 0; i < 9; i++)
					{
						sampleTex[i] = vec3(texture(screenTexture, texturePosition.st + offsets[i]));
					}
					vec3 col = vec3(0.0);
					for(int i = 0; i < 9; i++)
						col += sampleTex[i] * kernel[i];
					fragmentColor = vec4(col, 1.0);
				}
				else if (type == 2)
				{
					fragmentColor = vec4(vec3(1.0) - vec3(texture(screenTexture, texturePosition)), 1.0);
				}
				else
				{
					fragmentColor = vec4(vec3(texture(screenTexture, texturePosition)), 1.0);
				}
			}
		)"
	);
	const auto* window = static_cast<kernel::Window*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));
	BufferManager::create(HGUI_FRAMEBUFFER_POST_PROCESSING,
	                      ShaderManager::get(HGUI_SHADER_FRAMEBUFFER), window->get_size());
	ShaderManager::create(HGUI_SHADER_BUTTON,
	                      R"(
				#version 330 core

				layout (location = 0) in vec4 vertex;
				out vec2 texturePosition;

				uniform mat4 modelMatrix;
				uniform mat4 projectionMatrix;

				void main()
				{
					gl_Position = projectionMatrix * modelMatrix * vec4(vertex.xy, 0.0, 1.0);
					texturePosition = vertex.zw;
				}
			)",
	                      R"(
				#version 330 core
				in vec2 texturePosition;
				out vec4 fragmentColor;

				uniform sampler2D button;
				uniform vec4 buttonColor;

				uniform int focused;
				uniform bool custom;


				void main()
				{
					if (!custom)
					{
						fragmentColor = vec4(buttonColor);
					}
					else
					{
						fragmentColor = vec4(buttonColor) * texture(button, texturePosition);
					}
					if (focused == 1)
					{
						if (fragmentColor.w < 1)
						{
							float luminance = 0.2126 * fragmentColor.r + 0.7152 * fragmentColor.g + 0.0722 * fragmentColor.b;
							if (luminance > 0.5)
								fragmentColor = vec4(vec3(1.0), 0.05);
							else  
								fragmentColor = vec4(vec3(0.0), 0.05);
						}
						else
						{
							if (all(greaterThan(fragmentColor.xyz, vec3(0.1))))
								fragmentColor.xyz *= 0.9;
							else
								fragmentColor.xyz += 0.1;
						}

					}
					else if (focused == 2)
					{
						if (fragmentColor.w < 1)
						{
							float luminance = 0.2126 * fragmentColor.r + 0.7152 * fragmentColor.g + 0.0722 * fragmentColor.b;
							if (luminance > 0.5)
								fragmentColor = vec4(vec3(1.0), 0.1);
							else  
								fragmentColor = vec4(vec3(0.0), 0.1);
						}
						else
						{
							if (all(greaterThan(fragmentColor.xyz, vec3(0.1))))
								fragmentColor.xyz *= 0.8;
							else
								fragmentColor.xyz += 0.2;
						}
					}
				}
			)"
	);
	ShaderManager::create(HGUI_SHADER_LABEL,
	                      R"(
				#version 330 core

				layout (location = 0) in vec4 vertex;
				out vec2 texturePosition;

				uniform mat4 projectionMatrix;

				void main()
				{
					gl_Position = projectionMatrix * vec4(vertex.xy, 0.0, 1.0);
					texturePosition = vertex.zw;
				}
			)",
	                      R"(
				#version 330 core

				in vec2 texturePosition;
				out vec4 fragmentColor;

				uniform sampler2D text;
				uniform vec4 textColor;

				void main()
				{
					vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texturePosition).r);
					fragmentColor = vec4(textColor) * sampled;
				}
			)"
	);
	ShaderManager::create(HGUI_SHADER_SPRITE,
	                      R"(
				#version 330 core
				layout (location = 0) in vec4 vertex;

				out vec2 texturePosition;

				uniform mat4 modelMatrix;
				uniform mat4 projectionMatrix;

				void main()
				{
					texturePosition = vertex.zw;
					gl_Position = projectionMatrix * modelMatrix * vec4(vertex.xy, 0.0, 1.0);
				}
			)",
	                      R"(
				#version 330 core

				in vec2 texturePosition;
				out vec4 fragmentColor;

				uniform sampler2D sprite;
				uniform vec4 spriteColor;

				void main()
				{
					fragmentColor = vec4(spriteColor) * texture(sprite, texturePosition);
					if (fragmentColor.w < 1)
						discard;
				}
			)"
	);
	ShaderManager::create(HGUI_SHADER_CANVAS,
	                      R"(
				#version 330 core

				layout (location = 0) in vec2 vertex;
				layout (location = 1) in vec3 vertexColor;

				out vec3 color;

				uniform mat4 modelMatrix;
				uniform mat4 projectionMatrix;

				void main()
				{
					gl_Position = projectionMatrix * modelMatrix * vec4(vertex, 0.0, 1.0);
					color = vertexColor;
				}
			)",
	                      R"(
				#version 330 core

				in vec3 color;

				out vec4 fragmentColor;

				uniform vec2 canvasPosition;
				uniform vec2 canvasSize;

				void main()
				{
					fragmentColor = vec4(color, 1.0);
				}
			)"
	);
}

void hgui::kernel::resources_cleaner()
{
	FontManager::m_fonts.clear();
	CursorManager::m_cursors.clear();
	BufferManager::m_buffers.clear();
	ButtonManager::m_buttons.clear();
	SpriteManager::m_sprites.clear();
	LabelManager::m_labels.clear();
	CanvasManager::m_canvas.clear();
	WindowManager::m_windows.clear();
	Widget::m_binds.clear();
	Widget::m_widgets.clear();
	TagManager::m_tags.clear();
	MonitorManager::m_monitors.clear();
	KeyBoardManager::m_keys.clear();
}

void hgui::kernel::debug(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message,
                         const void* userParam)
{
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
		return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:
		std::cout << "Source: API";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		std::cout << "Source: Window System";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		std::cout << "Source: Shader Compiler";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		std::cout << "Source: Third Party";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		std::cout << "Source: Application";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		std::cout << "Source: Other";
		break;
	}
	std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:
		std::cout << "Type: Error";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		std::cout << "Type: Deprecated Behaviour";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		std::cout << "Type: Undefined Behaviour";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		std::cout << "Type: Portability";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		std::cout << "Type: Performance";
		break;
	case GL_DEBUG_TYPE_MARKER:
		std::cout << "Type: Marker";
		break;
	case GL_DEBUG_TYPE_PUSH_GROUP:
		std::cout << "Type: Push Group";
		break;
	case GL_DEBUG_TYPE_POP_GROUP:
		std::cout << "Type: Pop Group";
		break;
	case GL_DEBUG_TYPE_OTHER:
		std::cout << "Type: Other";
		break;
	}
	std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		std::cout << "Severity: high";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		std::cout << "Severity: medium";
		break;
	case GL_DEBUG_SEVERITY_LOW:
		std::cout << "Severity: low";
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		std::cout << "Severity: notification";
		break;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

bool hgui::kernel::init_glfw()
{
	static bool alreadyInitialized = false;
	if (!alreadyInitialized)
	{
		if (!glfwInit())
		{
			glfwTerminate();
			throw std::runtime_error("ERROR WITH GLFW LOADING");
		}
		alreadyInitialized = true;
		return alreadyInitialized;
	}
	else
	{
		throw std::runtime_error("GLFW ALREADY INITIALIZED");
	}
}
#endif
