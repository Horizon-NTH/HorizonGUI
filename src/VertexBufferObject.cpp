#include "../include/hgui/header/VertexBufferObject.h"

hgui::kernel::VertexBufferObject::VertexBufferObject() noexcept :
	m_id()
{
	glGenBuffers(1, &m_id);
}

hgui::kernel::VertexBufferObject::~VertexBufferObject() noexcept
{
	glDeleteBuffers(1, &m_id);
}

void hgui::kernel::VertexBufferObject::bind() const noexcept
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void hgui::kernel::VertexBufferObject::unbind() const noexcept
{
	(void)m_id;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void hgui::kernel::VertexBufferObject::set_data(const void* data, const int size, const bool dynamic) const noexcept
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

void hgui::kernel::VertexBufferObject::set_sub_data(const void* data, const int size, const int offset) const noexcept
{
	bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}
