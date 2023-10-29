#include <hgui/header/CursorManager.h>

#if defined(HGUI_DYNAMIC)
std::shared_ptr<hgui::kernel::Cursor> hgui::CursorManager::create(std::shared_ptr<kernel::Image>& cursor,
                                                                  const point& clickPosition)
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
#elif defined(HGUI_STATIC)
std::map<std::string, std::shared_ptr<hgui::kernel::Cursor>> hgui::CursorManager::m_cursors;

const std::shared_ptr<hgui::kernel::Cursor>& hgui::CursorManager::create(const std::string& cursorID,
                                                                         const std::shared_ptr<kernel::Image>& customCursor,
                                                                         const point& clickPosition)
{
	if (!m_cursors.contains(cursorID))
	{
		m_cursors[cursorID] = std::make_shared<kernel::Cursor>(customCursor, clickPosition);
		return m_cursors[cursorID];
	}
	else
	{
		throw std::runtime_error(("THERE IS ALREADY A CURSOR WITH THE ID : " + cursorID).c_str());
	}
}

const std::shared_ptr<hgui::kernel::Cursor>& hgui::CursorManager::get(const std::string& cursorID)
{
	if (m_cursors.contains(cursorID))
	{
		return m_cursors[cursorID];
	}
	else
	{
		throw std::runtime_error(("THERE IS NO CURSOR WITH THE ID : " + cursorID).c_str());
	}
}

void hgui::CursorManager::destroy(const std::initializer_list<std::string>& cursorsID)
{
	if (cursorsID.size())
	{
		for (const std::string& id : cursorsID)
		{
			m_cursors.erase(id);
		}
	}
	else
	{
		m_cursors.clear();
	}
}

void hgui::CursorManager::hide()
{
	glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void hgui::CursorManager::reveal()
{
	glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void hgui::CursorManager::init()
{
	m_cursors[HGUI_CURSOR_ARROW] = std::make_shared<kernel::Cursor>(cursors::ARROW);
	m_cursors[HGUI_CURSOR_IBEAM] = std::make_shared<kernel::Cursor>(cursors::IBEAM);
	m_cursors[HGUI_CURSOR_CROSSHAIR] = std::make_shared<kernel::Cursor>(cursors::CROSSHAIR);
	m_cursors[HGUI_CURSOR_HAND] = std::make_shared<kernel::Cursor>(cursors::HAND);
	m_cursors[HGUI_CURSOR_HRESIZE] = std::make_shared<kernel::Cursor>(cursors::HRESIZE);
	m_cursors[HGUI_CURSOR_VRESIZE] = std::make_shared<kernel::Cursor>(cursors::VRESIZE);
}
#endif
