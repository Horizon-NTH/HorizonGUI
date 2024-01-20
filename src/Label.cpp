#include "../include/hgui/header/Label.h"
#include "../include/hgui/header/VertexArrayObject.h"
#include "../include/hgui/header/VertexBufferObject.h"
#include "../include/hgui/header/Font.h"
#include "../include/hgui/header/Shader.h"
#include "../include/hgui/header/Texture.h"

hgui::kernel::Label::Label(std::string text, const std::shared_ptr<Shader>& shader, const point& position, const std::shared_ptr<Font>& font, const unsigned int fontSize, const color& color, const HGUI_PRECISION scale, const HGUI_PRECISION angularRotation) :
	Widget(shader, size(glm::vec2(0.0f)), position, color, angularRotation),
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
		const auto [texture, size, bearing, advance] = m_font->get_char(c, m_fontSize);
		m_size.em_height = EM<float>{} + std::max(size.height * m_scale, m_size.height);
		m_size.em_width += static_cast<float>(advance >> 6) * m_scale;
	}
	m_size.update();
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
		const auto [texture, size, bearing, advance] = m_font->get_char(c, m_fontSize);
		m_size.em_height = EM<float>{} + std::max(size.height * m_scale, m_size.height);
		m_size.em_width += static_cast<HGUI_PRECISION>(advance >> 6) * m_scale;
	}
	m_size.update();
}

void hgui::kernel::Label::set_width(const unsigned int newWidth)
{
	int max = 1000, min = 10;
	while (std::abs(m_size.width - static_cast<HGUI_PRECISION>(newWidth)) > size(1_em).width && max != min)
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
			const auto [texture, size, bearing, advance] = m_font->get_char(c, m_fontSize);
			m_size.em_height = EM<float>{} + std::max(size.height * m_scale, m_size.height);
			m_size.em_width += static_cast<HGUI_PRECISION>(advance >> 6) * m_scale;
		}
		m_size.update();
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
	while (std::abs(m_size.height - static_cast<HGUI_PRECISION>(newHeight)) > size(1_em).height && max != min)
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
			const auto [texture, size, bearing, advance] = m_font->get_char(c, m_fontSize);
			m_size.em_height = EM<float>{} + std::max(size.height * m_scale, m_size.height);
			m_size.em_width += static_cast<HGUI_PRECISION>(advance >> 6) * m_scale;
		}
		m_size.update();
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
	point position(m_position);
	const point center(m_position.x + m_size.width / 2.f, m_position.y + m_size.height / 2.f);
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
		const auto [texture, size, bearing, advance] = m_font->get_char(c, m_fontSize);

		const point pos = point(position.x + static_cast<float>(bearing.x), position.y + (static_cast<float>(m_font->get_char('H', m_fontSize).bearing.y) - static_cast<float>(bearing.y))) * m_scale;

		const float w = size.width * m_scale;
		const float h = size.height * m_scale;

		float vertices[6][4] = {
					{pos.x, pos.y + h, 0.0f, 1.0f},
					{pos.x + w, pos.y, 1.0f, 0.0f},
					{pos.x, pos.y, 0.0f, 0.0f},

					{pos.x, pos.y + h, 0.0f, 1.0f},
					{pos.x + w, pos.y + h, 1.0f, 1.0f},
					{pos.x + w, pos.y, 1.0f, 0.0f}
				};

		for (auto& vertex : vertices)
		{
			const point pt = point::rotate(point(vertex[0], vertex[1]), center, m_angularRotation);
			vertex[0] = pt.x;
			vertex[1] = pt.y;
		}
		texture->bind();
		m_VBO->bind();
		m_VBO->set_sub_data(vertices, sizeof(vertices), 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		position.em_x += static_cast<HGUI_PRECISION>(advance >> 6) * m_scale;
		position.update();
	}
	m_VAO->unbind();
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool hgui::kernel::Label::is_inside(const point& point) const
{
	const hgui::point center(m_position.x + m_size.width / 2.f, m_position.y + m_size.height / 2.f);
	const auto A = point::rotate(hgui::point(m_position.x, m_position.y), center, m_angularRotation),
			B = point::rotate(hgui::point(m_position.x + m_size.width, m_position.y), center, m_angularRotation),
			C = point::rotate(hgui::point(m_position.x + m_size.width, m_position.y + m_size.height), center, m_angularRotation),
			D = point::rotate(hgui::point(m_position.x, m_position.y + m_size.height), center, m_angularRotation);

	return point::is_in_rectangle(A, B, D, point);
}
