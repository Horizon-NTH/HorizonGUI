#include <hgui/header/Label.h>

hgui::kernel::Label::Label(std::string text, const std::shared_ptr<Shader>& shader, const point& position,
                           const std::shared_ptr<Font>& font, const unsigned int fontSize, const color& color,
                           const float scale) : Widget(shader, size(glm::vec2(0.0f)), position, color),
                                                m_text(std::move(text)),
                                                m_scale(scale),
                                                m_fontSize(fontSize),
                                                m_font(font)
{
	m_VAO->bind();
	m_VBO->set_data(nullptr, 24 * sizeof(float), true);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
	m_VAO->unbind();
	if (!m_font)
	{
		throw std::runtime_error("ERROR CANNOT CREATE TEXT WITHOUT SETTING A FONT");
	}
	if (!m_font->is_load(m_fontSize))
	{
		m_font->load_font(m_fontSize);
	}
	for (const char c : m_text)
	{
		const Character ch = m_font->get_char(c, m_fontSize);
		m_size.height = std::max(ch.size.height * m_scale, m_size.height);
		m_size.width += static_cast<float>(ch.advance >> 6) * m_scale;
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

void hgui::kernel::Label::set_font_size(const unsigned int fontSize)
{
	m_fontSize = fontSize;
}

void hgui::kernel::Label::set_text(const std::string& newText)
{
	m_text = newText;
	m_size = size();
	for (const char c : m_text)
	{
		const Character ch = m_font->get_char(c, m_fontSize);
		m_size.height = std::max(ch.size.height * m_scale, m_size.height);
		m_size.width += static_cast<HGUI_PRECISION>(ch.advance >> 6) * m_scale;
	}
}

void hgui::kernel::Label::set_width(const unsigned int newWidth)
{
	int max = 1000, min = 10;
	while (std::abs(hgui::size(m_size).width - static_cast<HGUI_PRECISION>(newWidth)) > hgui::size(1_em).width && max != min)
	{
		m_fontSize = (max + min) / 2;
		m_fontSize++;
		if (!m_font->is_load(m_fontSize))
		{
			m_font->load_font(m_fontSize);
		}
		m_size = size();
		for (const char c : m_text)
		{
			const Character ch = m_font->get_char(c, m_fontSize);
			m_size.height = std::max(ch.size.height * m_scale, m_size.height);
			m_size.width += static_cast<HGUI_PRECISION>(ch.advance >> 6) * m_scale;
		}
		if (m_size.width > static_cast<HGUI_PRECISION>(newWidth))
		{
			max = static_cast<int>(m_fontSize);
		}
		else
		{
			min = static_cast<int>(m_fontSize);
		}
	}
}

void hgui::kernel::Label::set_height(const unsigned int newHeight)
{
	int max = 1000, min = 10;
	while (std::abs(hgui::size(m_size).height - static_cast<HGUI_PRECISION>(newHeight)) > hgui::size(1_em).height && max != min)
	{
		m_fontSize = (max + min) / 2;
		m_fontSize++;
		if (!m_font->is_load(m_fontSize))
		{
			m_font->load_font(m_fontSize);
		}
		m_size = size();
		for (const char c : m_text)
		{
			const Character ch = m_font->get_char(c, m_fontSize);
			m_size.height = std::max(ch.size.height * m_scale, m_size.height);
			m_size.width += static_cast<HGUI_PRECISION>(ch.advance >> 6) * m_scale;
		}
		if (m_size.height > static_cast<HGUI_PRECISION>(newHeight))
		{
			max = static_cast<int>(m_fontSize);
		}
		else
		{
			min = static_cast<int>(m_fontSize);
		}
	}
}

void hgui::kernel::Label::draw() const
{
	const point position(m_position);
	int width, height;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
	m_shader->use().set_vec4("textColor", vec4(m_color))
	        .set_mat4("projectionMatrix", glm::ortho(0.0f, static_cast<float>(width),
	                                                 static_cast<float>(height), 0.f))
	        .set_int("text", 0);
	glActiveTexture(GL_TEXTURE0);
	m_VAO->bind();
	for (const char c : m_text)
	{
		const Character ch = m_font->get_char(c, m_fontSize);

		const float xpos = position.x + ch.bearing.x * m_scale;
		const float ypos = position.y + (m_font->get_char('H', m_fontSize).bearing.y - ch.bearing.y) * m_scale;

		const float w = ch.size.width * m_scale;
		const float h = ch.size.height * m_scale;

		const float vertices[6][4] = {
					{xpos, ypos + h, 0.0f, 1.0f},
					{xpos + w, ypos, 1.0f, 0.0f},
					{xpos, ypos, 0.0f, 0.0f},

					{xpos, ypos + h, 0.0f, 1.0f},
					{xpos + w, ypos + h, 1.0f, 1.0f},
					{xpos + w, ypos, 1.0f, 0.0f}
				};
		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		m_VBO->bind();
		m_VBO->set_sub_data(vertices, sizeof(vertices), 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		position.x += static_cast<HGUI_PRECISION>(ch.advance >> 6) * m_scale;
	}
	m_VAO->unbind();
	glBindTexture(GL_TEXTURE_2D, 0);
}
