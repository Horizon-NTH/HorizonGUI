#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"
#include "Image.h"

namespace hgui
{
	class CursorManager;

	namespace kernel
	{
		class Cursor
		{
			friend class CursorManager;

		public:
			Cursor(cursors standardCursor);
			Cursor(const std::shared_ptr<Image>& customCursor, const point& clickPosition);

			~Cursor();

			void use() const;

		private:

			GLFWcursor* m_cursorPTR;
		};
	}
}

