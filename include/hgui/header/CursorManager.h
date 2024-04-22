#pragma once

#include "Coordinate.hpp"

namespace hgui
{
	namespace kernel
	{
		class Image;
		class Cursor;
	}

#if defined(HGUI_DYNAMIC)
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
		static std::shared_ptr<kernel::Cursor> get_cursor_used();

	private:
		static inline std::weak_ptr<kernel::Cursor> m_cursorUsed;

		friend void kernel::resources_cleaner();
	};
#elif defined(HGUI_STATIC)
	class CursorManager
	{
	public:
		CursorManager() = delete;
		~CursorManager() = delete;
		CursorManager(const CursorManager& bufferManager) = delete;
		CursorManager(CursorManager&& bufferManager) = delete;

		CursorManager& operator=(const CursorManager& bufferManager) = delete;
		CursorManager& operator=(CursorManager&& bufferManager) = delete;

		static const std::shared_ptr<kernel::Cursor>& create(const std::string& cursorID, const std::shared_ptr<kernel::Image>& customCursor, const point& clickPosition);
		[[nodiscard]] static const std::shared_ptr<kernel::Cursor>& get(const std::string& cursorID);
		static void destroy(const std::initializer_list<std::string>& cursorsID = {});

		static void hide();
		static void reveal();
		static void disable();
		static void enable();
		static void use(const std::shared_ptr<kernel::Cursor>& cursor);
		static std::shared_ptr<kernel::Cursor> get_cursor_used();

	private:
		static void init();

		static std::map<std::string, std::shared_ptr<kernel::Cursor>> m_cursors;
		static std::weak_ptr<kernel::Cursor> m_cursorUsed;

		friend void init();
		friend void kernel::resources_cleaner();
	};
#endif
}
