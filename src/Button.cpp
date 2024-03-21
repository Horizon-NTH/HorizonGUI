#include "../include/hgui/header/Button.h"
#include "../include/hgui/header/VertexArrayObject.h"
#include "../include/hgui/header/VertexBufferObject.h"
#include "../include/hgui/header/Shader.h"
#include "../include/hgui/header/Label.h"
#include "../include/hgui/header/Texture.h"
#include "../include/hgui/header/Renderer.h"

hgui::kernel::Button::Button(const std::function<void()>& function, const std::shared_ptr<Shader>& shader, const size& size, const point& position, const std::shared_ptr<Label>& text, const std::tuple<color, color, color>& color, const HGUI_PRECISION rotation, const HGUI_PRECISION cornerRadius, const bool blurrOnHover, const std::shared_ptr<Texture>& texture) :
	Widget(shader, size, position, rotation),
	m_state(state::NORMAL),
	m_function(function),
	m_texture(texture),
	m_text(text),
	m_cornerRadius(std::clamp(cornerRadius, 0.f, 1.f)),
	m_cornerAngularRadius(std::min(m_size.width, m_size.height) * 0.5f * m_cornerRadius),
	m_modelMatrix(1.0),
	m_isTextDrawable(false),
	m_colors(color),
	m_blurrOnHover(blurrOnHover)
{
	set_texture(texture);
	Button::set_position(position);
	init_data();
	set_text_placment();
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
	[[maybe_unused]] auto& null = m_shader->use().set_mat4("modelMatrix", m_modelMatrix)
	                                      .set_mat4("projectionMatrix", glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.f, -1.0f, 1.0f))
	                                      .set_vec4("buttonColor", vec4(buttonColor)).set_int("focused", static_cast<int>(m_state))
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
	if (m_isTextDrawable and m_text)
	{
		m_text->draw();
	}
}

bool hgui::kernel::Button::is_inside(const point& point) const
{
	const hgui::point center = m_position + m_size / 2.f;
	const auto A = point::rotate(hgui::point(m_position.x, m_position.y), center, m_rotation),
			a = point::rotate(hgui::point(m_position.x + m_cornerAngularRadius, m_position.y + m_cornerAngularRadius), center, m_rotation),
			ap = point::rotate(hgui::point(m_position.x + m_cornerAngularRadius, m_position.y), center, m_rotation),
			B = point::rotate(hgui::point(m_position.x + m_size.width, m_position.y), center, m_rotation),
			b = point::rotate(hgui::point(m_position.x + m_size.width - m_cornerAngularRadius, m_position.y + m_cornerAngularRadius), center, m_rotation),
			bp = point::rotate(hgui::point(m_position.x + m_size.width - m_cornerAngularRadius, m_position.y), center, m_rotation),
			C = point::rotate(hgui::point(m_position.x + m_size.width, m_position.y + m_size.height), center, m_rotation),
			c = point::rotate(hgui::point(m_position.x + m_size.width - m_cornerAngularRadius, m_position.y + m_size.height - m_cornerAngularRadius), center, m_rotation),
			cp = point::rotate(hgui::point(m_position.x + m_size.width, m_position.y + m_size.height - m_cornerAngularRadius), center, m_rotation),
			D = point::rotate(hgui::point(m_position.x, m_position.y + m_size.height), center, m_rotation),
			d = point::rotate(hgui::point(m_position.x + m_cornerAngularRadius, m_position.y + m_size.height - m_cornerAngularRadius), center, m_rotation),
			dp = point::rotate(hgui::point(m_position.x, m_position.y + m_size.height - m_cornerAngularRadius), center, m_rotation);

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
	m_modelMatrix = translate(m_modelMatrix, glm::vec3(0.5f * m_size.width, 0.5f * m_size.height, 0.0f));
	m_modelMatrix = rotate(m_modelMatrix, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	m_modelMatrix = translate(m_modelMatrix, glm::vec3(-0.5f * m_size.width, -0.5f * m_size.height, 0.0f));
	m_modelMatrix = scale(m_modelMatrix, glm::vec3(m_size.width, m_size.height, 1.0f));
	set_text_placment();
}

void hgui::kernel::Button::set_size(const size& newSize)
{
	Widget::set_size(newSize);
	m_cornerAngularRadius = std::min(m_size.width, m_size.height) * 0.5f * m_cornerRadius;
	init_data();
	set_text_placment();
}

void hgui::kernel::Button::set_state(const state& state)
{
	m_state = state;
}

void hgui::kernel::Button::set_color(const std::tuple<color, color, color>& newColors)
{
	m_colors = newColors;
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

const std::shared_ptr<hgui::kernel::Label>& hgui::kernel::Button::get_text() const
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

void hgui::kernel::Button::set_texture(const std::shared_ptr<Texture>& texture)
{
	m_texture = texture;
}

void hgui::kernel::Button::set_text(const std::shared_ptr<Label>& text)
{
	m_text = text;
	set_text_placment();
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

void hgui::kernel::Button::set_text_placment()
{
	if (m_text)
	{
		const point b1 = m_position + point(m_cornerAngularRadius),
				b2 = m_position + m_size - point(m_cornerAngularRadius);
		point textPosition(b1);
		size textSize(b2);
		if (m_cornerAngularRadius < 5.f)
		{
			textPosition += point(5.f);
			textSize -= point(5.f) + textPosition;
		}
		else
		{
			textPosition += point::normalize(m_position - b1) * m_cornerAngularRadius;
			textSize += point::normalize(m_position + m_size - b2) * m_cornerAngularRadius - textPosition;
		}
		m_text->set_width(static_cast<unsigned>(textSize.width));
		if (m_text->get_size().height > textSize.height)
		{
			m_text->set_height(static_cast<unsigned>(textSize.height));
			if (m_text->get_size().width > textSize.width)
				m_isTextDrawable = false;
			else
				m_isTextDrawable = true;
		}
		const point gap = (textSize - m_text->get_size()) / 2.f;
		m_text->set_position(textPosition + gap);
	}
}
