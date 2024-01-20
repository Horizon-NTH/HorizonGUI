#include "../include/hgui/header/VertexArrayObject.h"

hgui::kernel::VertexArrayObject::VertexArrayObject() noexcept :
	m_id()
{
	glGenVertexArrays(1, &m_id);
}

hgui::kernel::VertexArrayObject::~VertexArrayObject() noexcept
{
	glDeleteVertexArrays(1, &m_id);
}

void hgui::kernel::VertexArrayObject::bind() const noexcept
{
	glBindVertexArray(m_id);
}

void hgui::kernel::VertexArrayObject::unbind() const noexcept
{
	(void)m_id;
	glBindVertexArray(0);
}
