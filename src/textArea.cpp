#include <hgui/header/TextArea.h>

hgui::kernel::TextArea::TextArea(const std::string& text, const std::shared_ptr<Shader>& shader, glm::vec2 position, const std::shared_ptr<Font> font, unsigned int fontSize, glm::vec3 color, float scale) :
    Widget(shader, glm::vec2(0.0f), position, color), m_text(text), m_font(font), m_scale(scale), m_fontSize(fontSize)
{
    m_VAO->bind();
    m_VBO->set_data(NULL, 24 * sizeof(float), true);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    m_VAO->unbind();
    if (!m_font)
    {
        throw std::exception("ERROR CANNOT CREATE TEXT WITHOUT SETTING A FONT");
    }
    if (!m_font->is_load(m_fontSize))
    {
        m_font->load_font(m_fontSize);
    }
    for (char c : m_text)
    {
        Character ch = m_font->get_char(c, m_fontSize);
        m_size.y = std::max(ch.size.y * m_scale, m_size.y);
        m_size.x += (ch.advance >> 6) * m_scale;
    }
}

std::string hgui::kernel::TextArea::get_text() const
{
    return m_text;
}

void hgui::kernel::TextArea::set_text(const std::string& newText)
{
    m_text = newText;
}

void hgui::kernel::TextArea::set_size(glm::vec2 newSize)
{
    if (m_size.x < newSize.x)
    {
        while (m_size.x < newSize.x)
        {
            m_fontSize++;
            if (!m_font->is_load(m_fontSize))
            {
                m_font->load_font(m_fontSize);
            }
            m_size = glm::vec2(0.0);
            for (char c : m_text)
            {
                Character ch = m_font->get_char(c, m_fontSize);
                m_size.y = std::max(ch.size.y * m_scale, m_size.y);
                m_size.x += (ch.advance >> 6) * m_scale;
            }
        }
    }
    else if (m_size.x > newSize.x)
    {
        while (m_size.x > newSize.x && m_fontSize > 0)
        {
            m_fontSize--;
            if (!m_font->is_load(m_fontSize))
            {
                m_font->load_font(m_fontSize);
            }/*
            for (char c : m_text)
            {
                Character ch = m_font->get_char(c, m_fontSize);
                m_size.y = std::max(ch.size.y * m_scale, m_size.y);
                m_size.x += (ch.advance >> 6) * m_scale;
            }*/
        }
    }
}

void hgui::kernel::TextArea::draw() const
{
    glm::vec2 position = m_position;
    kernel::Window* window = static_cast<kernel::Window*>(glfwGetWindowUserPointer(WindowManager::get_current_windowPTR()));
    m_shader->use().set_vec3f("textColor", m_color).set_mat4("projectionMatrix", glm::ortho(0.0f, static_cast<float>(window->get_size().x), static_cast<float>(window->get_size().y), 0.f)).set_1i("text", 0);
    glActiveTexture(GL_TEXTURE0);
    m_VAO->bind();
    for (char c : m_text)
    {
        Character ch = m_font->get_char(c, m_fontSize);

        float xpos = position.x + ch.bearing.x * m_scale;
        float ypos = position.y + (m_font->get_char('H', m_fontSize).bearing.y - ch.bearing.y) * m_scale;

        float w = ch.size.x * m_scale;
        float h = ch.size.y * m_scale;

        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f },
            { xpos,     ypos,       0.0f, 0.0f },

            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f }
        };
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        m_VBO->bind();
        m_VBO->set_sub_data(vertices, sizeof(vertices), 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        position.x += (ch.advance >> 6) * m_scale;
    }
    m_VAO->unbind();
    glBindTexture(GL_TEXTURE_2D, 0);
}