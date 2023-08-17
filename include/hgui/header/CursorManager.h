#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"
#include "Cursor.h"

namespace hgui
{
	namespace kernel
	{
		void resources_cleaner();
	}

	class CursorManager
	{
	public:
		static void create(const std::string& cursorID, const std::shared_ptr<kernel::Image>& customCursor, const point& clickPosition);
		static const std::shared_ptr<hgui::kernel::Cursor>& get(const std::string& cursorID);
		static void set(const std::string& cursorID);
		static void destroy(const std::initializer_list<std::string>& cursorsID = {});

	private:
		CursorManager() = delete;

		static void init();

		static std::map<std::string, std::shared_ptr<kernel::Cursor>> m_cursors;

		friend void init();
		friend void kernel::resources_cleaner();
	};
}

