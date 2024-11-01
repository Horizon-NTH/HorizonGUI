#pragma once

#include "Coordinate.hpp"

namespace hgui
{
	class CursorManager;

	namespace kernel
	{
		class Image;

		class Cursor
		{
			friend class CursorManager;

		public:
			explicit Cursor(cursors standardCursor);
			Cursor(const std::shared_ptr<Image>& customCursor, const point& clickPosition);
			Cursor(const Cursor& cursor) = delete;
			Cursor(Cursor&& cursor) = delete;

			~Cursor();

			Cursor& operator=(const Cursor& cursor) = delete;
			Cursor& operator=(Cursor&& cursor) = delete;

			[[nodiscard]] GLFWcursor* get_cursor_ptr() const;
			[[nodiscard]] cursors get_type() const;

			void make_custom_cursor(const std::shared_ptr<Image>& customCursor, const point& clickPosition);
			void make_standard_cursor(cursors standardCursor);

		private:
			GLFWcursor* m_cursorPTR;
			cursors m_type;
		};
	}
}
