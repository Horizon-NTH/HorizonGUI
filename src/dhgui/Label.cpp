#include <hgui/header/Label.h>

hgui::kernel::Label::Label(const std::string& text, const std::shared_ptr<Shader>& shader, const point& position, const std::shared_ptr<Font>& font, unsigned int fontSize, const color& color, float scale) :
	Widget(shader, glm::vec2(0.0f), position, color), m_text(text), m_font(font), m_scale(scale), m_fontSize(fontSize)
{
	m_VAO->bind();
	m_VBO->set_data(NULL, 24 * sizeof(float), true);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	m_VAO->unbind();
	if (!m_font)
	{
		throw std::runtime_error("ERROR CANNOT CREATE TEXT WITHOUT SETTING A FONT");
	}
	if (!m_font->is_load(m_fontSize))
	{
		m_font->load_font(m_fontSize);
	}
	for (char c : m_text)
	{
		Character ch = m_font->get_char(c, m_fontSize);
		m_size.height = std::max(ch.size.height * m_scale, m_size.height);
		m_size.width += (ch.advance >> 6) * m_scale;
	}
}

std::string hgui::kernel::Label::get_text() const
{
	return m_text;
}

unsigned int hgui::kernel::Label::get_font_size() const
{
	return m_fontSize;
}

void hgui::kernel::Label::set_font_size(unsigned int fontSize)
{
	m_fontSize = fontSize;
}

void hgui::kernel::Label::set_text(const std::string& newText)
{
	m_text = newText;
	m_size = size();
	for (char c : m_text)
	{
		Character ch = m_font->get_char(c, m_fontSize);
		m_size.height = std::max(ch.size.height * m_scale, m_size.height);
		m_size.width += (ch.advance >> 6) * m_scale;
	}
}

void hgui::kernel::Label::set_width(unsigned int newWidth)
{
	int max = 1000, min = 10;
	while (std::abs(hgui::size(m_size).width - newWidth) > hgui::size(1_em).width && max != min)
	{
		m_fontSize = (max + min) / 2;
		m_fontSize++;
		if (!m_font->is_load(m_fontSize))
		{
			m_font->load_font(m_fontSize);
		}
		m_size = size();
		for (char c : m_text)
		{
			Character ch = m_font->get_char(c, m_fontSize);
			m_size.height = std::max(ch.size.height * m_scale, m_size.height);
			m_size.width += (ch.advance >> 6) * m_scale;
		}
		if (m_size.width > newWidth)
		{
			max = m_fontSize;
		}
		else
		{
			min = m_fontSize;
		}
	}
}

void hgui::kernel::Label::set_height(unsigned int newHeight)
{
	int max = 1000, min = 10;
	while (std::abs(hgui::size(m_size).height - newHeight) > hgui::size(1_em).height && max != min)
	{
		m_fontSize = (max + min) / 2;
		m_fontSize++;
		if (!m_font->is_load(m_fontSize))
		{
			m_font->load_font(m_fontSize);
		}
		m_size = size();
		for (char c : m_text)
		{
			Character ch = m_font->get_char(c, m_fontSize);
			m_size.height = std::max(ch.size.height * m_scale, m_size.height);
			m_size.width += (ch.advance >> 6) * m_scale;
		}
		if (m_size.height > newHeight)
		{
			max = m_fontSize;
		}
		else
		{
			min = m_fontSize;
		}
	}
}

void hgui::kernel::Label::draw() const
{
	point position(m_position);
	int width, height;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
	m_shader->use().set_vec3("textColor", m_color)
		.set_mat4("projectionMatrix", glm::ortho(0.0f, static_cast<float>(width), 
			static_cast<float>(height), 0.f))
		.set_int("text", 0);
	glActiveTexture(GL_TEXTURE0);
	m_VAO->bind();
	for (char c : m_text)
	{
		Character ch = m_font->get_char(c, m_fontSize);

		float xpos = position.x + ch.bearing.x * m_scale;
		float ypos = position.y + (m_font->get_char('H', m_fontSize).bearing.y - ch.bearing.y) * m_scale;

		float w = ch.size.width * m_scale;
		float h = ch.size.height * m_scale;

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
