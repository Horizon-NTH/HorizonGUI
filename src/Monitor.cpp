#include <hgui/header/Monitor.h>

hgui::kernel::Monitor::Monitor(GLFWmonitor* monitorPTR) : m_monitorPTR(monitorPTR),
                                                          m_size(glfwGetVideoMode(monitorPTR)->width, glfwGetVideoMode(monitorPTR)->height),
                                                          m_name(glfwGetMonitorName(monitorPTR))
{
	int x, y;
	glfwGetMonitorPos(m_monitorPTR, &x, &y);
	m_position.x = static_cast<float>(x);
	m_position.y = static_cast<float>(y);
}

GLFWmonitor* hgui::kernel::Monitor::get_monitor_ptr() const
{
	return m_monitorPTR;
}

const hgui::size& hgui::kernel::Monitor::get_size() const
{
	return m_size;
}

std::string hgui::kernel::Monitor::get_name() const
{
	return m_name;
}

const hgui::point& hgui::kernel::Monitor::get_position() const
{
	return m_position;
}
