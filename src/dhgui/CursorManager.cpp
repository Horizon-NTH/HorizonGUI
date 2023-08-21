#include <hgui/header/CursorManager.h>

std::shared_ptr<hgui::kernel::Cursor> hgui::CursorManager::create(std::shared_ptr<kernel::Image>& cursor, const point& clickPosition)
{
	return std::make_shared<kernel::Cursor>(cursor, clickPosition);
}

std::shared_ptr<hgui::kernel::Cursor> hgui::CursorManager::create(cursors cursor)
{
	return std::make_shared<kernel::Cursor>(cursor);
}

void hgui::CursorManager::hide()
{
	glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void hgui::CursorManager::reveal()
{
	glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
