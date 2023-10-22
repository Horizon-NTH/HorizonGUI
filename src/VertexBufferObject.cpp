#include <hgui/header/VertexBufferObject.h>

hgui::kernel::VertexBufferObject::VertexBufferObject()
{
	glGenBuffers(1, &m_id);
}

hgui::kernel::VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &m_id);
}

void hgui::kernel::VertexBufferObject::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void hgui::kernel::VertexBufferObject::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void hgui::kernel::VertexBufferObject::set_data(const void* data, int size, bool dynamic)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

void hgui::kernel::VertexBufferObject::set_sub_data(const void* data, int size, int offset)
{
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}
