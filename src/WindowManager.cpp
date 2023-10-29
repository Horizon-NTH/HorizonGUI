#include <hgui/header/WindowManager.h>

#if defined(HGUI_DYNAMIC)
std::shared_ptr<hgui::kernel::Window> hgui::WindowManager::create(const std::string& windowName, const size& size, const point& position,
                                                                  const std::shared_ptr<kernel::Image>& icon,
                                                                  const std::shared_ptr<kernel::Monitor>& monitor,
                                                                  const std::initializer_list<std::pair<options, bool>>& options)
{
	auto window = std::make_shared<kernel::Window>(windowName, size, position, icon, monitor, options);
	glfwMakeContextCurrent(window->get_window_ptr());
	glfwSetScrollCallback(window->get_window_ptr(), MouseManager::scroll);
	glfwSetKeyCallback(window->get_window_ptr(), KeyBoardManager::input);
	glfwSetMouseButtonCallback(window->get_window_ptr(), MouseManager::input);
	kernel::init_glad();
	return window;
}
#elif defined(HGUI_STATIC)
std::map<std::string, std::shared_ptr<hgui::kernel::Window>> hgui::WindowManager::m_windows;

const std::shared_ptr<hgui::kernel::Window>& hgui::WindowManager::create(const std::string& windowID, const std::string& windowName,
                                                                         const size& size, const point& position,
                                                                         const std::shared_ptr<kernel::Image>& icon,
                                                                         const std::shared_ptr<kernel::Monitor>& monitor,
                                                                         const std::initializer_list<std::pair<options, bool>>& options)
{
	if (!m_windows.contains(windowID))
	{
		m_windows[windowID] = std::make_shared<kernel::Window>(windowName, size, position, icon, monitor, options);
		glfwMakeContextCurrent(m_windows[windowID]->get_window_ptr());
		glfwSetScrollCallback(m_windows[windowID]->get_window_ptr(), MouseManager::scroll);
		glfwSetKeyCallback(m_windows[windowID]->get_window_ptr(), KeyBoardManager::input);
		glfwSetMouseButtonCallback(m_windows[windowID]->get_window_ptr(), MouseManager::input);
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
	if (m_windows.contains(windowID))
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
		for (const std::string& id : windowsID)
		{
			m_windows.erase(id);
		}
	}
	else
	{
		m_windows.clear();
	}
}
#endif
