#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"
#include "Cursor.h"

namespace hgui
{
#if defined(HGUI_DYNAMIC)
	class CursorManager
	{
	public:
		static std::shared_ptr<kernel::Cursor> create(std::shared_ptr<kernel::Image>& cursor, const point& clickPosition);
		static std::shared_ptr<kernel::Cursor> create(cursors cursor);

		static void hide();
		static void reveal();

	private:
		CursorManager() = delete;
	};
#elif defined(HGUI_STATIC)
	class CursorManager
	{
	public:
		static const std::shared_ptr<kernel::Cursor>& create(const std::string& cursorID, const std::shared_ptr<kernel::Image>& customCursor, const point& clickPosition);
		static const std::shared_ptr<kernel::Cursor>& get(const std::string& cursorID);
		static void destroy(const std::initializer_list<std::string>& cursorsID = {});

		static void hide();
		static void reveal();

	private:
		CursorManager() = delete;

		static void init();

		static std::map<std::string, std::shared_ptr<kernel::Cursor>> m_cursors;

		friend void init();
		friend void kernel::resources_cleaner();
	};
#endif
}
