#include <hgui/header/WindowManager.h>

std::map<std::string, std::shared_ptr<hgui::kernel::Window>> hgui::WindowManager::m_windows;

const std::shared_ptr<hgui::kernel::Window>& hgui::WindowManager::create(const std::string& windowName, const size& size, const point& position, const std::shared_ptr<kernel::Image>& icon, const std::initializer_list<std::pair<options, bool>>& options)
{
	if (m_windows.find(windowName) == m_windows.end())
	{
		m_windows[windowName] = std::make_shared<kernel::Window>(windowName, size, position, icon, options);
		glfwMakeContextCurrent(m_windows[windowName]->get_windowPTR());
		glfwSetScrollCallback(m_windows[windowName]->get_windowPTR(), MouseManager::scroll);
		glfwSetKeyCallback(m_windows[windowName]->get_windowPTR(), KeyBoardManager::input);
		glfwSetMouseButtonCallback(m_windows[windowName]->get_windowPTR(), MouseManager::input);
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

void hgui::WindowManager::delete_windows(const std::initializer_list<std::string>& windowsNames)
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
