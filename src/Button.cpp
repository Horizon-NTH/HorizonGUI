#include "../include/hgui/header/Button.h"
#include "../include/hgui/header/VertexArrayObject.h"
#include "../include/hgui/header/VertexBufferObject.h"
#include "../include/hgui/header/Shader.h"
#include "../include/hgui/header/Label.h"
#include "../include/hgui/header/Texture.h"
#include "../include/hgui/header/Renderer.h"
#include "../include/hgui/header/Font.h"

hgui::kernel::Button::Button(const std::function<void()>& function, const std::shared_ptr<Shader>& shader, const size& size, const point& position, const std::shared_ptr<Label>& text, const std::tuple<color, color, color>& colors, const HGUI_PRECISION cornerRadius, const bool blurrOnHover, const std::shared_ptr<Texture>& texture) :
	Widget(shader, size, position),
	m_state(state::NORMAL),
	m_function(function),
	m_texture(texture),
	m_text(text),
	m_cornerRadius(std::clamp(cornerRadius, 0.f, 1.f)),
	m_cornerAngularRadius(std::min(m_size.width, m_size.height) * 0.5f * m_cornerRadius),
	m_modelMatrix(1.0),
	m_colors(colors),
	m_blurrOnHover(blurrOnHover),
	m_textValue(m_text ? m_text->get_text() : "")
{
	set_texture(texture);
	Button::set_position(position);
	init_data();
	if (m_text)
		m_text->set_alignement(false);
	set_text_placment();
	truncate_text();
}

void hgui::kernel::Button::press() const
{
	if (m_function)
	{
		m_function();
	}
}

void hgui::kernel::Button::draw() const
{
	int width, height;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
	color buttonColor;
	switch (m_state)
	{
		case state::NORMAL:
			buttonColor = std::get<0>(m_colors);
			break;
		case state::HOVER:
			buttonColor = std::get<1>(m_colors);
			break;
		case state::PRESS:
			buttonColor = std::get<2>(m_colors);
			break;
		default:
			break;
	}
	m_shader->use().set_mat4("modelMatrix", m_modelMatrix)
	        .set_mat4("projectionMatrix", glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.f, -1.0f, 1.0f))
	        .set_vec4("buttonColor", vec4(buttonColor))
	        .set_int("focused", static_cast<int>(m_state))
	        .set_int("custom", m_texture ? true : false)
	        .set_int("blurrOnHover", m_blurrOnHover);
	if (m_blurrOnHover)
	{
		const auto backgroundColor = Renderer::get_background_color();
		const float luminance = 0.2126f * backgroundColor.r + 0.7152f * backgroundColor.g + 0.0722f * backgroundColor.b;
		[[maybe_unused]] auto& _null = m_shader->set_int("dark", luminance < 0.5f);
	}
	m_VAO->bind();
	if (m_texture)
	{
		glActiveTexture(GL_TEXTURE0);
		m_texture->bind();
		m_shader->set_int("texture", 0);
	}
	glDrawArrays(GL_TRIANGLES, 0, 138);
	m_VAO->unbind();
}

bool hgui::kernel::Button::is_inside(const point& point) const
{
	const auto A = m_position,
			a = hgui::point(m_position.x + m_cornerAngularRadius, m_position.y + m_cornerAngularRadius),
			ap = hgui::point(m_position.x + m_cornerAngularRadius, m_position.y),
			B = hgui::point(m_position.x + m_size.width, m_position.y),
			b = hgui::point(m_position.x + m_size.width - m_cornerAngularRadius, m_position.y + m_cornerAngularRadius),
			bp = hgui::point(m_position.x + m_size.width - m_cornerAngularRadius, m_position.y),
			C = hgui::point(m_position.x + m_size.width, m_position.y + m_size.height),
			c = hgui::point(m_position.x + m_size.width - m_cornerAngularRadius, m_position.y + m_size.height - m_cornerAngularRadius),
			cp = hgui::point(m_position.x + m_size.width, m_position.y + m_size.height - m_cornerAngularRadius),
			D = hgui::point(m_position.x, m_position.y + m_size.height),
			d = hgui::point(m_position.x + m_cornerAngularRadius, m_position.y + m_size.height - m_cornerAngularRadius),
			dp = hgui::point(m_position.x, m_position.y + m_size.height - m_cornerAngularRadius);

	return point::is_in_rectangle(A, B, D, point) && !((point::is_in_rectangle(ap, a, A, point) && point::distance(point, a) >= m_cornerAngularRadius)
	                                                   || (point::is_in_rectangle(bp, B, b, point) && point::distance(point, b) >= m_cornerAngularRadius)
	                                                   || (point::is_in_rectangle(cp, C, c, point) && point::distance(point, c) >= m_cornerAngularRadius)
	                                                   || (point::is_in_rectangle(dp, d, D, point) && point::distance(point, d) >= m_cornerAngularRadius));
}

void hgui::kernel::Button::set_position(const point& newPosition)
{
	Widget::set_position(newPosition);
	m_modelMatrix = glm::mat4(1.0);
	m_modelMatrix = translate(m_modelMatrix, glm::vec3(m_position.x, m_position.y, 0.0f));
	m_modelMatrix = scale(m_modelMatrix, glm::vec3(m_size.width, m_size.height, 1.0f));
	set_text_placment();
}

void hgui::kernel::Button::set_size(const size& newSize)
{
	Widget::set_size(newSize);
	m_cornerAngularRadius = std::min(m_size.width, m_size.height) * 0.5f * m_cornerRadius;
	init_data();
	set_text_placment();
	truncate_text();
}

const hgui::state& hgui::kernel::Button::get_state() const
{
	return m_state;
}

const std::tuple<hgui::color, hgui::color, hgui::color>& hgui::kernel::Button::get_color() const
{
	return m_colors;
}

const std::shared_ptr<hgui::kernel::Texture>& hgui::kernel::Button::get_texture() const
{
	return m_texture;
}

const std::string& hgui::kernel::Button::get_text() const
{
	return m_textValue;
}

const std::shared_ptr<hgui::kernel::Label>& hgui::kernel::Button::get_label() const
{
	return m_text;
}

const std::function<void()>& hgui::kernel::Button::get_function() const
{
	return m_function;
}

bool hgui::kernel::Button::get_blurr_on_hover() const
{
	return m_blurrOnHover;
}

void hgui::kernel::Button::set_state(const state& state)
{
	m_state = state;
}

void hgui::kernel::Button::set_color(const std::tuple<color, color, color>& newColors)
{
	m_colors = newColors;
}

void hgui::kernel::Button::set_texture(const std::shared_ptr<Texture>& texture)
{
	m_texture = texture;
}

void hgui::kernel::Button::set_label(const std::shared_ptr<Label>& label)
{
	m_text = label;
	if (m_text)
	{
		m_text->set_alignement(false);
		m_textValue = m_text->get_text();
	}
	set_text_placment();
	truncate_text();
}

void hgui::kernel::Button::set_text(const std::string& text)
{
	m_textValue = text;
	set_text_placment();
	truncate_text();
}

void hgui::kernel::Button::set_function(const std::function<void()>& function)
{
	m_function = function;
}

void hgui::kernel::Button::set_blurr_on_hover(const bool blurrOnHover)
{
	m_blurrOnHover = blurrOnHover;
}

void hgui::kernel::Button::init_data()
{
	std::vector<glm::vec4> vertices = {
				//Position					//Texture Position
				{m_cornerAngularRadius, 0.0f, m_cornerAngularRadius, 0.0f},
				{m_cornerAngularRadius, m_cornerAngularRadius, m_cornerAngularRadius, m_cornerAngularRadius},
				{m_size.width - m_cornerAngularRadius, m_cornerAngularRadius, m_size.width - m_cornerAngularRadius, m_cornerAngularRadius},

				{m_cornerAngularRadius, 0.0f, m_cornerAngularRadius, 0.0f},
				{m_size.width - m_cornerAngularRadius, 0.0f, m_size.width - m_cornerAngularRadius, 0.0f},
				{m_size.width - m_cornerAngularRadius, m_cornerAngularRadius, m_size.width - m_cornerAngularRadius, m_cornerAngularRadius},

				{0.0f, m_cornerAngularRadius, 0.0f, m_cornerAngularRadius},
				{0.0f, m_size.height - m_cornerAngularRadius, 0.0f, m_size.height - m_cornerAngularRadius},
				{m_size.width, m_size.height - m_cornerAngularRadius, m_size.width, m_size.height - m_cornerAngularRadius},

				{0.0f, m_cornerAngularRadius, 0.0f, m_cornerAngularRadius},
				{m_size.width, m_cornerAngularRadius, m_size.width, m_cornerAngularRadius},
				{m_size.width, m_size.height - m_cornerAngularRadius, m_size.width, m_size.height - m_cornerAngularRadius},

				{
					m_cornerAngularRadius, m_size.height - m_cornerAngularRadius, m_cornerAngularRadius,
					m_size.height - m_cornerAngularRadius
				},
				{m_cornerAngularRadius, m_size.height, m_cornerAngularRadius, m_size.height},
				{m_size.width - m_cornerAngularRadius, m_size.height, m_size.width - m_cornerAngularRadius, m_size.height},

				{
					m_cornerAngularRadius, m_size.height - m_cornerAngularRadius, m_cornerAngularRadius,
					m_size.height - m_cornerAngularRadius
				},
				{
					m_size.width - m_cornerAngularRadius, m_size.height - m_cornerAngularRadius, m_size.width - m_cornerAngularRadius,
					m_size.height - m_cornerAngularRadius
				},
				{m_size.width - m_cornerAngularRadius, m_size.height, m_size.width - m_cornerAngularRadius, m_size.height},
			};
	constexpr int numSegments = 10;
	float angle;
	for (int i = 0; i < numSegments; i++)
	{
		angle = static_cast<float>(i) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_cornerAngularRadius - m_cornerAngularRadius * std::cos(angle),
			m_cornerAngularRadius - m_cornerAngularRadius * std::sin(angle),
			m_cornerAngularRadius - m_cornerAngularRadius * std::cos(angle),
			m_cornerAngularRadius - m_cornerAngularRadius * std::sin(angle));
		angle = static_cast<float>(i + 1) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_cornerAngularRadius - m_cornerAngularRadius * std::cos(angle),
			m_cornerAngularRadius - m_cornerAngularRadius * std::sin(angle),
			m_cornerAngularRadius - m_cornerAngularRadius * std::cos(angle),
			m_cornerAngularRadius - m_cornerAngularRadius * std::sin(angle));
		vertices.emplace_back(0.f + m_cornerAngularRadius, 0.0f + m_cornerAngularRadius, 0.f + m_cornerAngularRadius,
			0.0f + m_cornerAngularRadius);
	}
	for (int i = 0; i < numSegments; i++)
	{
		angle = static_cast<float>(i) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_size.width - m_cornerAngularRadius + m_cornerAngularRadius * std::cos(angle),
			m_cornerAngularRadius - m_cornerAngularRadius * std::sin(angle),
			m_size.width - m_cornerAngularRadius + m_cornerAngularRadius * std::cos(angle),
			m_cornerAngularRadius - m_cornerAngularRadius * std::sin(angle));
		angle = static_cast<float>(i + 1) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_size.width - m_cornerAngularRadius + m_cornerAngularRadius * std::cos(angle),
			m_cornerAngularRadius - m_cornerAngularRadius * std::sin(angle),
			m_size.width - m_cornerAngularRadius + m_cornerAngularRadius * std::cos(angle),
			m_cornerAngularRadius - m_cornerAngularRadius * std::sin(angle));
		vertices.emplace_back(m_size.width - m_cornerAngularRadius, 0.0f + m_cornerAngularRadius,
			m_size.width - m_cornerAngularRadius, 0.0f + m_cornerAngularRadius);
	}
	for (int i = 0; i < numSegments; i++)
	{
		angle = static_cast<float>(i) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_size.width - m_cornerAngularRadius + m_cornerAngularRadius * std::cos(angle),
			m_size.height - m_cornerAngularRadius + m_cornerAngularRadius * std::sin(angle),
			m_size.width - m_cornerAngularRadius + m_cornerAngularRadius * std::cos(angle),
			m_size.height - m_cornerAngularRadius + m_cornerAngularRadius * std::sin(angle));
		angle = static_cast<float>(i + 1) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_size.width - m_cornerAngularRadius + m_cornerAngularRadius * std::cos(angle),
			m_size.height - m_cornerAngularRadius + m_cornerAngularRadius * std::sin(angle),
			m_size.width - m_cornerAngularRadius + m_cornerAngularRadius * std::cos(angle),
			m_size.height - m_cornerAngularRadius + m_cornerAngularRadius * std::sin(angle));
		vertices.emplace_back(m_size.width - m_cornerAngularRadius, m_size.height - m_cornerAngularRadius,
			m_size.width - m_cornerAngularRadius, m_size.height - m_cornerAngularRadius);
	}
	for (int i = 0; i < numSegments; i++)
	{
		angle = static_cast<float>(i) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_cornerAngularRadius - m_cornerAngularRadius * std::cos(angle),
			m_size.height - m_cornerAngularRadius + m_cornerAngularRadius * std::sin(angle),
			m_cornerAngularRadius - m_cornerAngularRadius * std::cos(angle),
			m_size.height - m_cornerAngularRadius + m_cornerAngularRadius * std::sin(angle));
		angle = static_cast<float>(i + 1) * glm::pi<float>() / (2 * numSegments);
		vertices.emplace_back(m_cornerAngularRadius - m_cornerAngularRadius * std::cos(angle),
			m_size.height - m_cornerAngularRadius + m_cornerAngularRadius * std::sin(angle),
			m_cornerAngularRadius - m_cornerAngularRadius * std::cos(angle),
			m_size.height - m_cornerAngularRadius + m_cornerAngularRadius * std::sin(angle));
		vertices.emplace_back(0.0f + m_cornerAngularRadius, m_size.height - m_cornerAngularRadius, 0.0f + m_cornerAngularRadius,
			m_size.height - m_cornerAngularRadius);
	}
	const glm::mat4 normalize = {
				1.0f / m_size.width, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0 / m_size.height, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f / m_size.width, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f / m_size.height
			};
	for (auto& v : vertices)
	{
		v = normalize * v;
	}
	m_VAO->bind();
	m_VBO->bind();
	m_VBO->set_data(vertices.data(), static_cast<int>(vertices.size()) * static_cast<int>(sizeof(glm::vec4)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), static_cast<void*>(nullptr));
	m_VAO->unbind();
}

void hgui::kernel::Button::set_text_placment() const
{
	if (m_text)
	{
		const auto temp = m_text->get_text();
		m_text->set_text(m_textValue);
		m_text->set_height(static_cast<unsigned>(0.4f * m_size.height));
		m_text->set_text(temp);
		const auto size = m_text->get_size();
		point offset;
		if (size.width > m_size.width)
			offset = point(std::max(0.3f * m_size.height, 0.5f * m_cornerAngularRadius), 0.3f * m_size.height);
		else
			offset = point((m_size.em_width - m_text->get_size().em_width) * 0.5f, 0.3f * m_size.height);
		m_text->set_position(m_position + offset);
	}
}

void hgui::kernel::Button::truncate_text() const
{
	if (m_text)
	{
		unsigned totalAdvance = 0u;
		unsigned index = 0u;
		const auto& font = m_text->get_font();
		const auto maxWidth = static_cast<unsigned>(m_size.width - std::max(0.4f * m_size.height, m_cornerAngularRadius));
		while (totalAdvance < maxWidth && index < m_textValue.size())
		{
			totalAdvance += font->get_char(m_textValue[index], m_text->get_font_size()).advance >> 6;
			index++;
		}
		if (totalAdvance > maxWidth)
			--index;
		m_text->set_text(m_textValue.substr(0, index));
	}
}
