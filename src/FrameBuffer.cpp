#include <hgui/header/FrameBuffer.h>

hgui::kernel::FrameBuffer::FrameBuffer()
{
	glGenFramebuffers(1, &m_id);
}

hgui::kernel::FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_id);
}

void hgui::kernel::FrameBuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

void hgui::kernel::FrameBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void hgui::kernel::FrameBuffer::clear() const
{
	bind();
	glClear(GL_COLOR_BUFFER_BIT);
	unbind();
}

GLuint hgui::kernel::FrameBuffer::get_id() const
{
	return m_id;
}

bool hgui::kernel::FrameBuffer::is_complete() const
{
	bind();
	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

void hgui::kernel::FrameBuffer::attach_texture(const std::shared_ptr<hgui::kernel::Texture>& texture) const
{
	bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->get_id(), 0);
	unbind();
}

void hgui::kernel::FrameBuffer::attach_render_buffer(const std::shared_ptr<hgui::kernel::RenderBuffer>& renderBuffer) const
{
	bind();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer->get_id());
	unbind();
}
