#include "../include/hgui/header/Cursor.h"
#include "../include/hgui/header/Image.h"

hgui::kernel::Cursor::Cursor(cursors standardCursor) :
	m_cursorPTR(glfwCreateStandardCursor(static_cast<int>(standardCursor)))
{
}

hgui::kernel::Cursor::Cursor(const std::shared_ptr<Image>& customCursor, const point& clickPosition) :
	m_cursorPTR(nullptr)
{
	const GLFWimage cursor
			{
				.width = static_cast<int>(customCursor->get_data().width),
				.height = static_cast<int>(customCursor->get_data().height),
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
	glfwDestroyCursor(m_cursorPTR);
}

void hgui::kernel::Cursor::use() const
{
	glfwSetCursor(glfwGetCurrentContext(), m_cursorPTR);
}
