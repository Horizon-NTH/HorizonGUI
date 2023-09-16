#include <hgui/header/WindowManager.h>

std::map<std::string, std::shared_ptr<hgui::kernel::Window>> hgui::WindowManager::m_windows;

const std::shared_ptr<hgui::kernel::Window>& hgui::WindowManager::create(const std::string& windowID, const std::string& windowName, const size& size, const point& position, const std::shared_ptr<kernel::Image>& icon, const std::shared_ptr<kernel::Monitor>& monitor, const std::initializer_list<std::pair<options, bool>>& options)
{
	if (m_windows.find(windowID) == m_windows.end())
	{
		m_windows[windowID] = std::make_shared<kernel::Window>(windowName, size, position, icon, monitor, options);
		glfwMakeContextCurrent(m_windows[windowID]->get_windowPTR());
		glfwSetScrollCallback(m_windows[windowID]->get_windowPTR(), MouseManager::scroll);
		glfwSetKeyCallback(m_windows[windowID]->get_windowPTR(), KeyBoardManager::input);
		glfwSetMouseButtonCallback(m_windows[windowID]->get_windowPTR(), MouseManager::input);
		kernel::init_glad();
		kernel::init_resources();
		return m_windows[windowID];
	}
	else
	{
		throw std::runtime_error(("THERE IS ALREADY A WINDOW WITH THE ID : " + windowID).c_str());
	}
}

const std::shared_ptr<hgui::kernel::Window>& hgui::WindowManager::get(const std::string& windowID)
{
	if (m_windows.find(windowID) != m_windows.end())
	{
		return m_windows[windowID];
	}
	else
	{
		throw std::runtime_error(("THERE IS NO WINDOW WITH THE ID : " + windowID).c_str());
	}
}

void hgui::WindowManager::destroy(const std::initializer_list<std::string>& windowsID)
{
	if (windowsID.size())
	{
		for (const std::string& windowID : windowsID)
		{
			m_windows.erase(windowID);
		}
	}
	else
	{
		m_windows.clear();
	}
}
