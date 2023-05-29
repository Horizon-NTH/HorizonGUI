#include <hgui/header/WindowManager.h>

std::map<std::string, std::shared_ptr<hgui::kernel::Window>> hgui::WindowManager::m_windows;

const std::shared_ptr<hgui::kernel::Window>& hgui::WindowManager::create(const std::string& windowName, glm::vec2 size, glm::vec2 position = glm::vec2(0.0), const std::shared_ptr<kernel::Image>& icon, std::initializer_list<std::pair<kernel::WindowOptions, bool>> options)
{
	if (m_windows.find(windowName) == m_windows.end())
	{
		m_windows[windowName] = std::make_shared<kernel::Window>(windowName, size, position, icon, options);
		glfwMakeContextCurrent(m_windows[windowName]->get_windowPTR());
		glfwSetScrollCallback(m_windows[windowName]->get_windowPTR(), MouseManager::scroll);
		kernel::init_glad();
		kernel::init_resources();
		return m_windows[windowName];
	}
	else
	{
		throw std::exception(("THERE IS ALREADY A WINDOW WITH THE NAME : " + windowName).c_str());
	}
}

const std::shared_ptr<hgui::kernel::Window>& hgui::WindowManager::get(const std::string& windowName)
{
	if (m_windows.find(windowName) != m_windows.end())
	{
		return m_windows[windowName];
	}
	else
	{
		throw std::exception(("THERE IS NO WINDOW WITH THE NAME : " + windowName).c_str());
	}
}

void hgui::WindowManager::delete_windows(std::initializer_list<std::string> windowsNames)
{
	if (windowsNames.size())
	{
		for (const std::string& str : windowsNames)
		{
			m_windows.erase(str);
		}
	}
	else
	{
		m_windows.clear();
	}
}

GLFWwindow* hgui::WindowManager::get_current_windowPTR()
{
	return glfwGetCurrentContext();
}
