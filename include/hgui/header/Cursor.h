#pragma once

#include "Include.h"
#include "WindowManager.h"
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
			Cursor(int standardCursor);
			Cursor(const std::shared_ptr<Image>& customCursor, glm::vec2 clickPosition);

			~Cursor();

			void use() const;

		private:
			GLFWcursor* m_cursorPTR;
		};
	}
}

