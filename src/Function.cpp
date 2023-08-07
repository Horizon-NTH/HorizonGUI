#include <hgui/header/Function.h>

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
	glfwSetWindowShouldClose(WindowManager::get_current_windowPTR(), true);
}

void hgui::kernel::init_glad()
{
	if (glfwGetCurrentContext())
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			glfwTerminate();
			throw std::exception("ERROR WITH GLAD LOADING");
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
		throw std::exception("WINDOW NEEDED TO INITIALIZED GLAD");
	}
}

void hgui::kernel::init_resources()
{
	kernel::Window* window = static_cast<kernel::Window*>(glfwGetWindowUserPointer(WindowManager::get_current_windowPTR()));
	ResourceManager::load_shader(HGUI_SHADER_FRAMEBUFFER, 
		ResourceManager::m_glsl["VertexShaderFrameBuffer.glsl"], ResourceManager::m_glsl["FragmentShaderFrameBuffer.glsl"]);
	BufferManager::create(HGUI_FRAMEBUFFER_POST_PROCESSING, 
		ResourceManager::get_shader(HGUI_SHADER_FRAMEBUFFER), window->get_size());
	ResourceManager::load_shader(HGUI_SHADER_BUTTON, 
		ResourceManager::m_glsl["VertexShaderButton.glsl"], ResourceManager::m_glsl["FragmentShaderButton.glsl"]);
	ResourceManager::load_shader(HGUI_SHADER_TEXTAREA, 
		ResourceManager::m_glsl["VertexShaderText.glsl"], ResourceManager::m_glsl["FragmentShaderText.glsl"]);
	ResourceManager::load_shader(HGUI_SHADER_SPRITE, 
		ResourceManager::m_glsl["VertexShaderSprites.glsl"], ResourceManager::m_glsl["FragmentShaderSprites.glsl"]);
	ResourceManager::load_shader(HGUI_SHADER_CANVA, 
		ResourceManager::m_glsl["VertexShaderCanva.glsl"], ResourceManager::m_glsl["FragmentShaderCanva.glsl"]);
}

void hgui::kernel::resources_cleaner()
{
	FontManager::m_fonts.clear();
	CursorManager::m_cursors.clear();
	KeyBoardManager::m_keys.clear();
	BufferManager::m_buffers.clear();
	ButtonManager::m_buttons.clear();
	SpriteManager::m_sprites.clear();
	LabelManager::m_textAreas.clear();
	Widget::m_binds.clear();
	TagManager::m_tags.clear();
	MonitorManager::m_monitors.clear();
	WindowManager::m_windows.clear();
}

void hgui::kernel::debug(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam)
{
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
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
		throw std::exception("GLFW ALREADY INITIALIZED");
	}
}
