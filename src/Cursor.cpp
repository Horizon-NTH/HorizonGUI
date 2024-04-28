#include "../include/hgui/header/Cursor.h"
#include "../include/hgui/header/Image.h"

hgui::kernel::Cursor::Cursor(cursors standardCursor) :
	m_cursorPTR(nullptr),
	m_type(standardCursor)
{
	if (standardCursor == cursors::CUSTOM)
	{
		throw std::runtime_error("STANDARD CURSOR EXPECTED");
	}
	m_cursorPTR = glfwCreateStandardCursor(static_cast<int>(standardCursor));
}

hgui::kernel::Cursor::Cursor(const std::shared_ptr<Image>& customCursor, const point& clickPosition) :
	m_cursorPTR(nullptr),
	m_type(cursors::CUSTOM)
{
	const GLFWimage cursor
			{
				.width = static_cast<int>(customCursor->get_size().width),
				.height = static_cast<int>(customCursor->get_size().height),
				.pixels = customCursor->get_data().pixels.get()
			};
	if (cursor.pixels)
	{
		m_cursorPTR = glfwCreateCursor(&cursor, static_cast<int>(clickPosition.x), static_cast<int>(clickPosition.y));
	}
	else
	{
		throw std::runtime_error("IMAGE EXPECTED TO CREATE A CURSOR");
	}
}

hgui::kernel::Cursor::~Cursor()
{
	if (m_cursorPTR)
	{
		glfwDestroyCursor(m_cursorPTR);
	}
}

GLFWcursor* hgui::kernel::Cursor::get_cursor_ptr() const
{
	return m_cursorPTR;
}

hgui::cursors hgui::kernel::Cursor::get_type() const
{
	return m_type;
}

void hgui::kernel::Cursor::make_custom_cursor(const std::shared_ptr<Image>& customCursor, const point& clickPosition)
{
	const GLFWimage cursor
			{
				.width = static_cast<int>(customCursor->get_size().width),
				.height = static_cast<int>(customCursor->get_size().height),
				.pixels = customCursor->get_data().pixels.get()
			};
	if (!cursor.pixels)
	{
		throw std::runtime_error("IMAGE EXPECTED TO CREATE A CURSOR");
	}
	m_cursorPTR = glfwCreateCursor(&cursor, static_cast<int>(clickPosition.x), static_cast<int>(clickPosition.y));
	m_type = cursors::CUSTOM;
}

void hgui::kernel::Cursor::make_standard_cursor(cursors standardCursor)
{
	if (standardCursor == cursors::CUSTOM)
	{
		throw std::runtime_error("STANDARD CURSOR EXPECTED");
	}
	m_cursorPTR = glfwCreateStandardCursor(static_cast<int>(standardCursor));
	m_type = standardCursor;
}
