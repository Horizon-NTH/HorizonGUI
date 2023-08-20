#include <hgui/header/Texture.h>

hgui::kernel::Texture::Texture(const std::shared_ptr<Image>& image) :
    m_image(image)
{
    glGenTextures(1, &m_id);
    generate();
}

hgui::kernel::Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}

void hgui::kernel::Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

GLuint hgui::kernel::Texture::get_id() const
{
    return m_id;
}

const std::shared_ptr<hgui::kernel::Image>& hgui::kernel::Texture::get_image() const
{
    return m_image;
}

void hgui::kernel::Texture::generate()
{
    bind();
    ImageData data = m_image->get_data();
    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLenum>(data.channel), data.width, data.height, 0, static_cast<GLenum>(data.channel), GL_UNSIGNED_BYTE, data.pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}
