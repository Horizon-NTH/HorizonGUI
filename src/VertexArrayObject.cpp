#include <hgui/header/VertexArrayObject.h>

hgui::kernel::VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &m_id);
}

hgui::kernel::VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &m_id);
}

void hgui::kernel::VertexArrayObject::bind() const
{
	glBindVertexArray(m_id);
}

void hgui::kernel::VertexArrayObject::unbind()
{
	glBindVertexArray(0);
}
