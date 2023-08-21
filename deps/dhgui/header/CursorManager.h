#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"
#include "Cursor.h"

namespace hgui
{
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
}
