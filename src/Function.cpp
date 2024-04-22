#include "../include/hgui/header/Function.h"
#include "../include/hgui/header/MonitorManager.h"
#include "../include/hgui/header/SoundPlayerManager.h"
#include "../include/hgui/header/TagManager.h"
#include "../include/hgui/header/ButtonManager.h"
#include "../include/hgui/header/SpriteManager.h"
#include "../include/hgui/header/LabelManager.h"
#include "../include/hgui/header/CanvasManager.h"
#include "../include/hgui/header/SliderManager.h"
#include "../include/hgui/header/KeyBoardManager.h"
#include "../include/hgui/header/MouseManager.h"
#include "../include/hgui/header/Timer.h"

#if defined(HGUI_DYNAMIC)
void hgui::init()
{
	static bool alreadyInitialize = false;
	if (!alreadyInitialize)
	{
		kernel::init_glfw();
		MonitorManager::init();
		SoundPlayerManager::init();
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
	SpriteManager::m_shader = nullptr;
	LabelManager::m_shader = nullptr;
	CanvasManager::m_shader = nullptr;
	Widget::m_binds.clear();
	Widget::m_bindedTags.clear();
	Widget::m_widgets.clear();
	TagManager::m_tags.clear();
	KeyBoardManager::m_keys.clear();
	MouseManager::m_inputs.clear();
	SoundPlayerManager::clean();
}

void hgui::kernel::debug(const GLenum source, const GLenum type, const unsigned int id, const GLenum severity, [[maybe_unused]] GLsizei length, const char* message, [[maybe_unused]] const void* userParam)
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
		default:
			std::cout << "Source: Unknow";
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
		default:
			std::cout << "Type: Unknow";
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
		default:
			std::cout << "Severity: Unknow";
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
	throw std::runtime_error("GLFW ALREADY INITIALIZED");
}
#elif defined(HGUI_STATIC)
#include "../include/hgui/header/GLSL.h"
#include "../include/hgui/header/BufferManager.h"
#include "../include/hgui/header/WindowManager.h"
#include "../include/hgui/header/FontManager.h"

void hgui::init()
{
	static bool alreadyInitialize = false;
	if (!alreadyInitialize)
	{
		kernel::init_glfw();
		MonitorManager::init();
		SoundPlayerManager::init();
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
	ShaderManager::create(HGUI_SHADER_FRAMEBUFFER, HGUI_GLSL_VERTEX_BUFFER, HGUI_GLSL_FRAGMENT_BUFFER);
	const auto* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));
	BufferManager::create(HGUI_FRAMEBUFFER_POST_PROCESSING,
		ShaderManager::get(HGUI_SHADER_FRAMEBUFFER), size(100_em));
	ShaderManager::create(HGUI_SHADER_BUTTON, HGUI_GLSL_VERTEX_BUTTON, HGUI_GLSL_FRAGMENT_BUTTON);
	ShaderManager::create(HGUI_SHADER_LABEL, HGUI_GLSL_VERTEX_LABEL, HGUI_GLSL_FRAGMENT_LABEL);
	ShaderManager::create(HGUI_SHADER_SPRITE, HGUI_GLSL_VERTEX_SPRITE, HGUI_GLSL_FRAGMENT_SPRITE);
	ShaderManager::create(HGUI_SHADER_CANVAS, HGUI_GLSL_VERTEX_CANVAS, HGUI_GLSL_FRAGMENT_CANVAS);
	ShaderManager::create(HGUI_SHADER_CIRCLE, HGUI_GLSL_VERTEX_CIRCLE, HGUI_GLSL_FRAGMENT_CIRCLE);
	ShaderManager::create(HGUI_SHADER_RECTANGLE, HGUI_GLSL_VERTEX_RECTANGLE, HGUI_GLSL_FRAGMENT_RECTANGLE);
	ShaderManager::create(HGUI_SHADER_TRIANGLE, HGUI_GLSL_VERTEX_TRIANGLE, HGUI_GLSL_FRAGMENT_TRIANGLE);
	ShaderManager::create(HGUI_SHADER_STRAIGHTLINE, HGUI_GLSL_VERTEX_STRAIGHTLINE, HGUI_GLSL_FRAGMENT_STRAIGHTLINE);
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
	SoundPlayerManager::clean();
	MouseManager::m_inputs.clear();
}

void hgui::kernel::debug(const GLenum source, const GLenum type, const unsigned int id, const GLenum severity, [[maybe_unused]] GLsizei length, const char* message, [[maybe_unused]] const void* userParam)
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
		default:
			std::cout << "Source: Unknow";
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
		default:
			std::cout << "Type: Unknow";
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
		default:
			std::cout << "Severity: Unknow";
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
	throw std::runtime_error("GLFW ALREADY INITIALIZED");
}
#endif
