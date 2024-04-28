#include "../include/hgui/header/WindowManager.h"
#include "../include/hgui/header/Window.h"
#include "../include/hgui/header/MouseManager.h"
#include "../include/hgui/header/KeyBoardManager.h"
#include "../include/hgui/header/Function.h"

std::shared_ptr<hgui::kernel::Window> hgui::WindowManager::create(const std::string& windowName, const size& size, const point& position, const std::shared_ptr<kernel::Image>& icon, const std::shared_ptr<kernel::Monitor>& monitor, const std::map<options, bool>& options)
{
	auto window = std::make_shared<kernel::Window>(windowName, size, position, icon, monitor, options);
	glfwMakeContextCurrent(window->get_window_ptr());
	glfwSetScrollCallback(window->get_window_ptr(), MouseManager::scroll);
	glfwSetKeyCallback(window->get_window_ptr(), KeyBoardManager::input);
	glfwSetMouseButtonCallback(window->get_window_ptr(), MouseManager::input);
	kernel::init_glad();
	return window;
}
