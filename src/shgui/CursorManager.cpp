#include <hgui/header/CursorManager.h>

std::map<std::string, std::shared_ptr<hgui::kernel::Cursor>> hgui::CursorManager::m_cursors;

const std::shared_ptr<hgui::kernel::Cursor>& hgui::CursorManager::create(const std::string& cursorID, const std::shared_ptr<kernel::Image>& customCursor, const point& clickPosition)
{
	if (m_cursors.find(cursorID) == m_cursors.end())
	{
		m_cursors[cursorID] = std::make_shared<kernel::Cursor>(customCursor, clickPosition);
		return m_cursors[cursorID];
	}
	else
	{
		throw std::runtime_error(("THERE IS ALREADY A CUSOR WITH THE ID : " + cursorID).c_str());
	}
}

const std::shared_ptr<hgui::kernel::Cursor>& hgui::CursorManager::get(const std::string& cursorID)
{
	if (m_cursors.find(cursorID) != m_cursors.end())
	{
		return m_cursors[cursorID];
	}
	else
	{
		throw std::runtime_error(("THERE IS NO CUSOR WITH THE ID : " + cursorID).c_str());
	}
}

void hgui::CursorManager::destroy(const std::initializer_list<std::string>& cursorsID)
{
	if (cursorsID.size())
	{
		for (const std::string& cursorID : cursorsID)
		{
			m_cursors.erase(cursorID);
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
