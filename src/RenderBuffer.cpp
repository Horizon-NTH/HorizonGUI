#include <hgui/header/RenderBuffer.h>

hgui::kernel::RenderBuffer::RenderBuffer()
{
	glGenRenderbuffers(1, &m_id);
}

hgui::kernel::RenderBuffer::~RenderBuffer()
{
	glDeleteRenderbuffers(1, &m_id);
}

void hgui::kernel::RenderBuffer::bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, m_id);
}

void hgui::kernel::RenderBuffer::unbind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void hgui::kernel::RenderBuffer::create_depth_stencil()
{
	bind();
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, static_cast<GLsizei>(MonitorManager::get_primary_monitor()->get_size().x), static_cast<GLsizei>(MonitorManager::get_primary_monitor()->get_size().y));
	unbind();
}

GLuint hgui::kernel::RenderBuffer::get_id() const
{
	return m_id;
}
