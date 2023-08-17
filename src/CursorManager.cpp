#include <hgui/header/CursorManager.h>

std::map<std::string, std::shared_ptr<hgui::kernel::Cursor>> hgui::CursorManager::m_cursors;

void hgui::CursorManager::create(const std::string& cursorID, const std::shared_ptr<kernel::Image>& customCursor, const point& clickPosition)
{
	if (m_cursors.find(cursorID) == m_cursors.end())
	{
		m_cursors[cursorID] = std::make_shared<kernel::Cursor>(customCursor, clickPosition);
	}
	else
	{
		throw std::exception(("THERE IS ALREADY A CUSOR WITH THE ID : " + cursorID).c_str());
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
		throw std::exception(("THERE IS NO CUSOR WITH THE ID : " + cursorID).c_str());
	}
}

void hgui::CursorManager::set(const std::string& cursorID)
{
	if (m_cursors.find(cursorID) != m_cursors.end())
	{
		m_cursors[cursorID]->use();
	}
	else
	{
		throw std::exception(("THERE IS NO CUSOR WITH THE ID : " + cursorID).c_str());
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

void hgui::CursorManager::init()
{
	m_cursors[HGUI_CURSOR_ARROW] = std::make_shared<kernel::Cursor>(0x00036001);
	m_cursors[HGUI_CURSOR_IBEAM] = std::make_shared<kernel::Cursor>(0x00036002);
	m_cursors[HGUI_CURSOR_CROSSHAIR] = std::make_shared<kernel::Cursor>(0x00036003);
	m_cursors[HGUI_CURSOR_HAND] = std::make_shared<kernel::Cursor>(0x00036004);
	m_cursors[HGUI_CURSOR_HRESIZE] = std::make_shared<kernel::Cursor>(0x00036005);
	m_cursors[HGUI_CURSOR_VRESIZE] = std::make_shared<kernel::Cursor>(0x00036006);
}
