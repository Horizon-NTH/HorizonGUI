#include <hgui/header/CursorManager.h>

std::shared_ptr<hgui::kernel::Cursor> hgui::CursorManager::create(std::shared_ptr<kernel::Image>& cursor, const point& clickPosition)
{
	return std::make_shared<kernel::Cursor>(cursor, clickPosition);
}

std::shared_ptr<hgui::kernel::Cursor> hgui::CursorManager::create(cursors cursor)
{
	return std::make_shared<kernel::Cursor>(cursor);
}
