#include "../include/hgui/header/Label.h"
#include "../include/hgui/header/VertexArrayObject.h"
#include "../include/hgui/header/VertexBufferObject.h"
#include "../include/hgui/header/Font.h"
#include "../include/hgui/header/Shader.h"
#include "../include/hgui/header/Texture.h"

hgui::kernel::Label::Label(std::string text, const std::shared_ptr<Shader>& shader, const point& position, const std::shared_ptr<Font>& font, const unsigned int fontSize, const color& color, const bool align, const HGUI_PRECISION scale, const HGUI_PRECISION rotation) :
	Widget(shader, size(glm::vec2(0.0f)), position),
	m_text(std::move(text)),
	m_scale(scale),
	m_fontSize(fontSize),
	m_font(font),
	m_color(color),
	m_align(align),
	m_rotation(rotation)
{
	m_VAO->bind();
	m_VBO->set_data(nullptr, 24 * sizeof(float), true);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
	m_VAO->unbind();
	if (!m_font)
		throw std::runtime_error("ERROR CANNOT CREATE TEXT WITHOUT SETTING A FONT");
	if (!m_font->is_load(m_fontSize))
		m_font->load_font(m_fontSize);
	calcul_size();
}

std::string hgui::kernel::Label::get_text() const
{
	return m_text;
}

const hgui::color& hgui::kernel::Label::get_color() const
{
	return m_color;
}

unsigned int hgui::kernel::Label::get_font_size() const
{
	return m_fontSize;
}

const std::shared_ptr<hgui::kernel::Font>& hgui::kernel::Label::get_font() const
{
	return m_font;
}

bool hgui::kernel::Label::is_align() const
{
	return m_align;
}

HGUI_PRECISION hgui::kernel::Label::get_scale() const
{
	return m_scale;
}

HGUI_PRECISION hgui::kernel::Label::get_rotation() const
{
	return m_rotation;
}

void hgui::kernel::Label::set_font_size(const unsigned int fontSize)
{
	m_fontSize = fontSize;
}

void hgui::kernel::Label::set_text(const std::string& newText)
{
	m_text = newText;
	calcul_size();
}

void hgui::kernel::Label::set_color(const color& newColor)
{
	m_color = newColor;
}

void hgui::kernel::Label::set_font(const std::shared_ptr<Font>& font)
{
	if (!font)
		throw std::runtime_error("ERROR CANNOT SET A NULLPTR FONT");
	m_font = font;
	if (!m_font->is_load(m_fontSize))
		m_font->load_font(m_fontSize);
	calcul_size();
}

void hgui::kernel::Label::set_alignement(const bool align)
{
	m_align = align;
}

void hgui::kernel::Label::set_scale(const HGUI_PRECISION scale)
{
	m_scale = scale;
	calcul_size();
}

void hgui::kernel::Label::set_rotation(const HGUI_PRECISION rotation)
{
	m_rotation = rotation;
}

void hgui::kernel::Label::set_width(const unsigned int newWidth)
{
	int max = 1000, min = 10;
	while (std::abs(m_size.width - static_cast<HGUI_PRECISION>(newWidth)) > 1.f && max != min)
	{
		m_fontSize = static_cast<unsigned>(ceil(static_cast<float>((min + max)) / 2.f));
		if (!m_font->is_load(m_fontSize))
		{
			m_font->load_font(m_fontSize);
		}
		calcul_size();
		if (m_size.width >= static_cast<HGUI_PRECISION>(newWidth) && max != m_fontSize)
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
	while (std::abs(m_size.height - static_cast<HGUI_PRECISION>(newHeight)) > 1.f && max != min)
	{
		m_fontSize = static_cast<unsigned>(ceil(static_cast<float>((min + max)) / 2.f));
		if (!m_font->is_load(m_fontSize))
		{
			m_font->load_font(m_fontSize);
		}
		calcul_size();
		if (m_size.height >= static_cast<HGUI_PRECISION>(newHeight) && max != m_fontSize)
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
	const auto maxBearing = static_cast<float>(get_max_bearing_y());
	for (const char c : m_text)
	{
		const auto [texture, size, bearing, advance] = m_font->get_char(c, m_fontSize);

		const point pos = point(position.x + static_cast<float>(bearing.x), position.y + (maxBearing - static_cast<float>(bearing.y))) * m_scale;

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
			const point pt = point::rotate(point(vertex[0], vertex[1]), center, m_rotation);
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
	const auto A = point::rotate(hgui::point(m_position.x, m_position.y), center, m_rotation),
			B = point::rotate(hgui::point(m_position.x + m_size.width, m_position.y), center, m_rotation),
			C = point::rotate(hgui::point(m_position.x + m_size.width, m_position.y + m_size.height), center, m_rotation),
			D = point::rotate(hgui::point(m_position.x, m_position.y + m_size.height), center, m_rotation);

	return point::is_in_rectangle(A, B, D, point);
}

void hgui::kernel::Label::calcul_size()
{
	m_size = size();
	for (const char c : m_text)
	{
		const auto [texture, size, bearing, advance] = m_font->get_char(c, m_fontSize);
		m_size.em_height = EM<float>{} + std::max(size.height * m_scale, m_size.height);
		m_size.em_width += static_cast<float>(advance >> 6) * m_scale;
		m_size.update();
	}
	m_size.undo_responsivness();
}

int hgui::kernel::Label::get_max_bearing_y() const
{
	if (m_text.empty())
		return 0;
	const auto text = m_align ? m_font->get_printable_characters(m_fontSize) : m_text;
	return std::accumulate(
		std::next(text.begin()), text.end(),
		m_font->get_char(text[0], m_fontSize).bearing.y,
		[this](const int max, const char c)
			{
				return std::max(max, m_font->get_char(c, m_fontSize).bearing.y);
			}
	);
}
