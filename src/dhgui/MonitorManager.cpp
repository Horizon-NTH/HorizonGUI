#include <hgui/header/MonitorManager.h>

std::map<std::string, std::shared_ptr<hgui::kernel::Monitor>> hgui::MonitorManager::m_monitors;

const std::shared_ptr<hgui::kernel::Monitor>& hgui::MonitorManager::get(const std::string& monitorName)
{
    if (m_monitors.find(monitorName) != m_monitors.end())
    {
        return m_monitors[monitorName];
    }
    else
    {
        throw std::runtime_error(("THERE IS NO MONITOR WITH THE NAME : " + monitorName).c_str());
    }
}

const std::vector<std::string> hgui::MonitorManager::get_monitors_names()
{
    std::vector<std::string> monitorsNames;
    for (const auto& monitor : m_monitors)
    {
        monitorsNames.push_back(monitor.first);
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
