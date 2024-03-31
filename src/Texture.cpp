#include "../include/hgui/header/Texture.h"
#include "../include/hgui/header/Image.h"

hgui::kernel::Texture::Texture(const std::shared_ptr<Image>& image, const TextureOption options) :
	m_id(),
	m_image(image),
	m_options(options)
{
	glGenTextures(1, &m_id);
	generate();
}

hgui::kernel::Texture::~Texture() noexcept
{
	glDeleteTextures(1, &m_id);
}

void hgui::kernel::Texture::bind() const noexcept
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}

GLuint hgui::kernel::Texture::get_id() const noexcept
{
	return m_id;
}

const std::shared_ptr<hgui::kernel::Image>& hgui::kernel::Texture::get_image() const noexcept
{
	return m_image;
}

void hgui::kernel::Texture::generate() const
{
	bind();
	const auto& [size, channel, pixels] = m_image->get_data();
	const auto format = (channel == channels::GREYSCALE_ALPHA) ? channels::RGBA : channel;
	glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(format), static_cast<GLsizei>(size.width), static_cast<GLsizei>(size.height), 0, static_cast<GLenum>(format),
		GL_UNSIGNED_BYTE, pixels.get());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_options.wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_options.wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_options.min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_options.mag_filter);
	glBindTexture(GL_TEXTURE_2D, 0);
}
