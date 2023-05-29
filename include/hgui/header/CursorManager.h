#pragma once

#include "Include.h"
#include "Define.h"
#include "Cursor.h"
#include "Tools.h"

namespace hgui
{
	namespace kernel
	{
		class Cursor;
		void resources_cleaner();
	}

	class CursorManager
	{
	public:
		static void create(const std::string& cursorName, const std::shared_ptr<kernel::Image>& customCursor, glm::vec2 clickPosition);
		static const std::shared_ptr<hgui::kernel::Cursor>& get(const std::string& cursorName);
		static void set(const std::string& cursorName);
		static void delete_cursor(std::initializer_list<std::string> cursorsNames = {});

	private:
		CursorManager();

		static void init();

		static std::map<std::string, std::shared_ptr<kernel::Cursor>> m_cursors;

		friend void init();
		friend void kernel::resources_cleaner();
	};
}

