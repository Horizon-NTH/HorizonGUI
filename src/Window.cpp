#include "../include/hgui/header/Window.h"
#include "../include/hgui/header/Widget.h"
#include "../include/hgui/header/Monitor.h"
#include "../include/hgui/header/Image.h"
#include "../include/hgui/header/Renderer.h"

hgui::kernel::Window::Window(const std::string& name, const size& size, point position, const std::shared_ptr<Image>& icon, const std::shared_ptr<Monitor>& monitor, const std::map<options, bool>& options) :
	m_name(name),
	m_size(size),
	m_position(std::move(position))
{
	for (const auto& [option, state] : options)
	{
		glfwWindowHint(static_cast<int>(option), state);
	}
#ifndef HGUI_DEBUG_VERSION
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#else
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif
	glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
	m_windowPTR = glfwCreateWindow(static_cast<int>(size.width), static_cast<int>(size.height), name.c_str(),
		monitor ? monitor->get_monitor_ptr() : nullptr, nullptr);
	if (!m_windowPTR)
	{
		glfwTerminate();
		throw std::runtime_error("ERROR WITH WINDOW CREATION");
	}
	glfwSetWindowUserPointer(m_windowPTR, this);
	glfwSetWindowSizeCallback(m_windowPTR, size_callback);
	glfwSetWindowPosCallback(m_windowPTR, position_callback);
	if (icon)
	{
		const auto& [size, channel, pixels] = icon->get_data();
		const GLFWimage ico
				{
					.width = static_cast<int>(size.width),
					.height = static_cast<int>(size.height),
					.pixels = pixels.get()
				};
		glfwSetWindowIcon(m_windowPTR, 1, &ico);
	}
	glfwPollEvents();
	int width, height;
	glfwGetFramebufferSize(m_windowPTR, &width, &height);
	size_callback(m_windowPTR, width, height);
}

hgui::kernel::Window::~Window()
{
	if (glfwGetCurrentContext())
	{
		glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
		glfwDestroyWindow(m_windowPTR);
	}
}

const hgui::size& hgui::kernel::Window::get_size() const
{
	return m_size;
}

void hgui::kernel::Window::set_size(const size& newSize) const
{
	glfwSetWindowSize(m_windowPTR, static_cast<int>(newSize.width), static_cast<int>(newSize.height));
}

const hgui::point& hgui::kernel::Window::get_position() const
{
	return m_position;
}

void hgui::kernel::Window::set_position(const point& newPosition)
{
	m_position = newPosition;
	glfwSetWindowPos(m_windowPTR, static_cast<int>(newPosition.x), static_cast<int>(newPosition.y));
}

GLFWwindow* hgui::kernel::Window::get_window_ptr() const
{
	return m_windowPTR;
}

void hgui::kernel::Window::set_size_callback(const std::variant<std::function<void()>, SizeCallback>& function)
{
	m_sizeCallback = function;
}

void hgui::kernel::Window::set_position_callback(const std::variant<std::function<void()>, PositionCallback>& function)
{
	m_positionCallback = function;
}

void hgui::kernel::Window::size_callback(GLFWwindow* window, const int width, const int height)
{
	if (width == 0 || height == 0)
		return;
	auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (win->m_size.width == static_cast<float>(width) && win->m_size.height == static_cast<float>(height))
		return;
	if (glad_glViewport != nullptr)
		glViewport(0, 0, width, height);
	win->m_size = size(width, height);
	EM<HGUI_PRECISION>::referenceSize = std::make_pair(win->m_size.width, win->m_size.height);
	Widget::update();
	Renderer::buffer_update();
	if (const auto function = std::get_if<std::function<void()>>(&win->m_sizeCallback))
	{
		if (*function)
		{
			(*function)();
		}
	}
	else if (const auto functionWithParameter = std::get_if<SizeCallback>(&win->m_sizeCallback))
	{
		if (*functionWithParameter)
		{
			(*functionWithParameter)(window, width, height);
		}
	}
}

void hgui::kernel::Window::position_callback(GLFWwindow* window, const int xPosition, const int yPosition)
{
	const auto win = static_cast<Window*>(glfwGetWindowUserPointer(window));
	win->m_position = point(xPosition, yPosition);
	if (const auto function = std::get_if<std::function<void()>>(&win->m_positionCallback))
	{
		if (*function)
		{
			(*function)();
		}
	}
	else if (const auto functionWithParameter = std::get_if<PositionCallback>(&win->m_positionCallback))
	{
		if (*functionWithParameter)
		{
			(*functionWithParameter)(window, xPosition, yPosition);
		}
	}
}
