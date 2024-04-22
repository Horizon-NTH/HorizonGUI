#include "../include/hgui/header/MonitorManager.h"
#include "../include/hgui/header/Monitor.h"

const std::shared_ptr<hgui::kernel::Monitor>& hgui::MonitorManager::get(const std::string& monitorName)
{
	if (m_monitors.contains(monitorName))
	{
		return m_monitors[monitorName];
	}
	throw std::runtime_error(("THERE IS NO MONITOR WITH THE NAME : " + monitorName).c_str());
}

std::vector<std::string> hgui::MonitorManager::get_monitors_names()
{
	std::vector<std::string> monitorsNames;
	monitorsNames.reserve(m_monitors.size());
	for (const auto& monitor : m_monitors | std::ranges::views::keys)
	{
		monitorsNames.push_back(monitor);
	}
	return monitorsNames;
}

const std::shared_ptr<hgui::kernel::Monitor>& hgui::MonitorManager::get_primary_monitor()
{
	return m_monitors[glfwGetMonitorName(glfwGetPrimaryMonitor())];
}

void hgui::MonitorManager::init()
{
	int monitorNumber;
	GLFWmonitor** monitors = glfwGetMonitors(&monitorNumber);
	for (int i = 0; i < monitorNumber; i++)
	{
		m_monitors[glfwGetMonitorName(monitors[i])] = std::make_shared<kernel::Monitor>(monitors[i]);
	}
}
