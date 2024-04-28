#include "../include/hgui/header/CursorManager.h"
#include "../include/hgui/header/Cursor.h"

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

void hgui::CursorManager::disable()
{
	glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void hgui::CursorManager::enable()
{
	reveal();
}

void hgui::CursorManager::use(const std::shared_ptr<kernel::Cursor>& cursor)
{
	m_cursorUsed = cursor;
	glfwSetCursor(glfwGetCurrentContext(), cursor ? cursor->get_cursor_ptr() : nullptr);
}

std::shared_ptr<hgui::kernel::Cursor> hgui::CursorManager::get_cursor_used()
{
	return m_cursorUsed.lock();
}
