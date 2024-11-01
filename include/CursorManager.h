#pragma once

#include "Coordinate.hpp"

namespace hgui
{
	namespace kernel
	{
		class Image;
		class Cursor;
	}

	class CursorManager
	{
	public:
		CursorManager() = delete;
		~CursorManager() = delete;
		CursorManager(const CursorManager& cursorManager) = delete;
		CursorManager(CursorManager&& cursorManager) = delete;

		CursorManager& operator=(const CursorManager& cursorManager) = delete;
		CursorManager& operator=(CursorManager&& cursorManager) = delete;

		[[nodiscard]] static std::shared_ptr<kernel::Cursor> create(std::shared_ptr<kernel::Image>& cursor, const point& clickPosition);
		[[nodiscard]] static std::shared_ptr<kernel::Cursor> create(cursors cursor);

		static void hide();
		static void reveal();
		static void disable();
		static void enable();
		static void use(const std::shared_ptr<kernel::Cursor>& cursor);
		[[nodiscard]] static std::shared_ptr<kernel::Cursor> get_cursor_used();

	private:
		static inline std::weak_ptr<kernel::Cursor> m_cursorUsed;

		friend void kernel::resources_cleaner();
	};
}
