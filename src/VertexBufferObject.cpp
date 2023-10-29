#include <hgui/header/VertexBufferObject.h>

hgui::kernel::VertexBufferObject::VertexBufferObject()
{
	glGenBuffers(1, &m_id);
}

hgui::kernel::VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &m_id);
}

void hgui::kernel::VertexBufferObject::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void hgui::kernel::VertexBufferObject::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void hgui::kernel::VertexBufferObject::set_data(const void* data, const int size, const bool dynamic) const
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

void hgui::kernel::VertexBufferObject::set_sub_data(const void* data, const int size, const int offset) const
{
	bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}
