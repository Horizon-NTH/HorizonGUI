#include <hgui/header/Window.h>

hgui::kernel::Window::Window(const std::string& name, const size& size, const point& position, const std::shared_ptr<Image>& icon, const std::initializer_list<std::pair<options, bool>>& options) :
	m_name(name), m_size(size), m_position(position)
{
	for (const auto& option : options)
	{
		glfwWindowHint(static_cast<int>(option.first), option.second);
	}
#ifndef DEBUG
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#else
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif
	m_windowPTR = glfwCreateWindow(static_cast<int>(size.width), static_cast<int>(size.height), name.c_str(), NULL, NULL);
	if (!m_windowPTR)
	{
		glfwTerminate();
		throw std::runtime_error("ERROR WITH WINDOW CREATION");
	}
	glfwSetWindowUserPointer(m_windowPTR, this);
	glfwSetFramebufferSizeCallback(m_windowPTR, size_callback);
	if (icon)
	{
		ImageData data = icon->get_data();
		GLFWimage ico{ .width = data.width, .height = data.height, .pixels = data.pixels };
		glfwSetWindowIcon(m_windowPTR, 1, &ico);
	}
	int width, height;
	glfwGetFramebufferSize(m_windowPTR, &width, &height);
	size_callback(m_windowPTR, width, height);
}

hgui::kernel::Window::~Window()
{
	glfwDestroyWindow(m_windowPTR);
}

const hgui::size& hgui::kernel::Window::get_size() const
{
	return m_size;
}

void hgui::kernel::Window::set_size(const size& newSize)
{
	glfwSetWindowSize(m_windowPTR, static_cast<int>(newSize.width), static_cast<int>(newSize.height));
	size_callback(m_windowPTR, static_cast<int>(newSize.width), static_cast<int>(newSize.height));
}

void hgui::kernel::Window::set_fullscreen(const std::shared_ptr<Monitor>& monitor)
{
	glfwSetWindowMonitor(m_windowPTR, monitor->get_monitorPTR(), static_cast<int>(monitor->get_position().x),
		static_cast<int>(monitor->get_position().y), static_cast<int>(monitor->get_size().width), 
		static_cast<int>(monitor->get_size().height),
		glfwGetVideoMode(monitor->get_monitorPTR())->refreshRate);
	size_callback(m_windowPTR, static_cast<int>(m_size.width), static_cast<int>(m_size.height));
}

const hgui::point& hgui::kernel::Window::get_position()
{
	return m_position;
}

void hgui::kernel::Window::set_position(const point& newPosition)
{
	glfwSetWindowPos(m_windowPTR, static_cast<int>(newPosition.x), static_cast<int>(newPosition.y));
}

GLFWwindow* hgui::kernel::Window::get_windowPTR() const
{
	return m_windowPTR;
}

void hgui::kernel::Window::size_callback(GLFWwindow* window, int width, int height)
{
	Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (glad_glViewport != NULL)
		glViewport(0, 0, width, height);
	win->m_size = glm::vec2(width, height);
}

void hgui::kernel::Window::position_callback(GLFWwindow* window, int xPostion, int yPosition)
{
	Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
	win->m_position = glm::vec2(xPostion, yPosition);
}
