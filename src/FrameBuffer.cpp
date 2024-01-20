#include "../include/hgui/header/FrameBuffer.h"
#include "../include/hgui/header/Texture.h"
#include "../include/hgui/header/RenderBuffer.h"

hgui::kernel::FrameBuffer::FrameBuffer() noexcept :
	m_id()
{
	glGenFramebuffers(1, &m_id);
}

hgui::kernel::FrameBuffer::~FrameBuffer() noexcept
{
	glDeleteFramebuffers(1, &m_id);
}

void hgui::kernel::FrameBuffer::bind() const noexcept
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

void hgui::kernel::FrameBuffer::unbind() const noexcept
{
	(void)m_id;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void hgui::kernel::FrameBuffer::clear() const noexcept
{
	bind();
	glClear(GL_COLOR_BUFFER_BIT);
	unbind();
}

GLuint hgui::kernel::FrameBuffer::get_id() const noexcept
{
	return m_id;
}

bool hgui::kernel::FrameBuffer::is_complete() const noexcept
{
	bind();
	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

void hgui::kernel::FrameBuffer::attach_texture(const std::shared_ptr<Texture>& texture) const noexcept
{
	bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->get_id(), 0);
	unbind();
}

void hgui::kernel::FrameBuffer::attach_render_buffer(const std::shared_ptr<RenderBuffer>& renderBuffer) const noexcept
{
	bind();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer->get_id());
	unbind();
}
