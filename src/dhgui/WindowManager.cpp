#include <hgui/header/WindowManager.h>

std::shared_ptr<hgui::kernel::Window> hgui::WindowManager::create(const std::string& windowName, const size& size, const point& position, const std::shared_ptr<kernel::Image>& icon, const std::shared_ptr<kernel::Monitor>& monitor, const std::initializer_list<std::pair<options, bool>>& options)
{
	auto window = std::make_shared<kernel::Window>(windowName, size, position, icon, monitor, options);
	glfwMakeContextCurrent(window->get_windowPTR());
	glfwSetScrollCallback(window->get_windowPTR(), MouseManager::scroll);
	glfwSetKeyCallback(window->get_windowPTR(), KeyBoardManager::input);
	glfwSetMouseButtonCallback(window->get_windowPTR(), MouseManager::input);
	kernel::init_glad();
	return window;
}
