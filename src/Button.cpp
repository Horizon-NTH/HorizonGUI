#include <hgui/header/Button.h>

#include <cmath>

hgui::kernel::Button::Button(const std::function<void()>& function, const std::shared_ptr<Shader>& shader, const size& size, const point& position, const std::shared_ptr<Label>& text, const color& color, const HGUI_PRECISION angularRotation, const HGUI_PRECISION cornerAngularRadius, const std::shared_ptr<Texture>& texture) :
	Widget(shader, size, position, color, angularRotation),
	m_state(state::NORMAL),
	m_function(function),
	m_text(text),
	m_cornerAngularRadius(std::min(std::min(size.width, size.height) * 0.5f, cornerAngularRadius)),
	m_modelMatrix(1.0)
{
	set_textures(texture);
	Button::set_position(position);
	init_data();
	if (m_text)
	{
		m_text->set_width(static_cast<unsigned int>(std::max(m_size.width / 2, m_size.width - 2 * std::max(m_cornerAngularRadius, 5.f))));
		if (m_text->get_size().height > m_size.height - std::max(m_cornerAngularRadius, 5.f))
		{
			m_text->set_height(static_cast<unsigned int>(std::max(m_size.height / 2, m_size.height - 2 * std::max(m_cornerAngularRadius, 5.f))));
		}
		m_text->set_position(point(m_position + (m_size - m_text->get_size()) / 2) + (m_cornerAngularRadius <= 1e-6f ? point(2.5f, 0.f) : point(0)));
	}
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
	m_shader->use().set_mat4("modelMatrix", m_modelMatrix)
		.set_mat4("projectionMatrix", glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.f, -1.0f, 1.0f))
		.set_vec4("buttonColor", vec4(m_color)).set_int("focused", static_cast<int>(m_state))
		.set_int("custom", m_texture ? true : false);
	m_VAO->bind();
	if (m_texture)
	{
		glActiveTexture(GL_TEXTURE0);
		m_texture->bind();
		m_shader->set_int("texture", 0);
	}
	glDrawArrays(GL_TRIANGLES, 0, 138);
	m_VAO->unbind();
	if (m_text)
	{
		m_text->draw();
	}
}

bool hgui::kernel::Button::is_inside(const point& point) const
{
	const hgui::point center(m_position.x + m_size.width / 2.f, m_position.y + m_size.height / 2.f);
	const auto A = hgui::point::rotate(hgui::point(m_position.x, m_position.y), center, m_angularRotation),
		B = hgui::point::rotate(hgui::point(m_position.x + m_size.width, m_position.y), center, m_angularRotation),
		C = hgui::point::rotate(hgui::point(m_position.x + m_size.width, m_position.y + m_size.height), center, m_angularRotation),
		D = hgui::point::rotate(hgui::point(m_position.x, m_position.y + m_size.height), center, m_angularRotation),
		a = hgui::point::rotate(hgui::point(m_position.x + m_cornerAngularRadius, m_position.y + m_cornerAngularRadius), center, m_angularRotation),
		ap = hgui::point::rotate(hgui::point(m_position.x + m_cornerAngularRadius, m_position.y), center, m_angularRotation),
		b = hgui::point::rotate(hgui::point(m_position.x + m_size.width - m_cornerAngularRadius, m_position.y + m_cornerAngularRadius), center, m_angularRotation),
		bp = hgui::point::rotate(hgui::point(m_position.x + m_size.width - m_cornerAngularRadius, m_position.y), center, m_angularRotation),
		c = hgui::point::rotate(hgui::point(m_position.x + m_size.width - m_cornerAngularRadius, m_position.y + m_size.height - m_cornerAngularRadius), center, m_angularRotation),
		cp = hgui::point::rotate(hgui::point(m_position.x + m_size.width, m_position.y + m_size.height - m_cornerAngularRadius), center, m_angularRotation),
		d = hgui::point::rotate(hgui::point(m_position.x + m_cornerAngularRadius, m_position.y + m_size.height - m_cornerAngularRadius), center, m_angularRotation),
		dp = hgui::point::rotate(hgui::point(m_position.x, m_position.y + m_size.height - m_cornerAngularRadius), center, m_angularRotation);

	return hgui::point::is_in_rectangle(A, B, D, point) && !((hgui::point::is_in_rectangle(ap, a, A, point) && hgui::kernel::distance(point, a) >= m_cornerAngularRadius)
		|| (hgui::point::is_in_rectangle(bp, B, b, point) && hgui::kernel::distance(point, b) >= m_cornerAngularRadius)
		|| (hgui::point::is_in_rectangle(cp, c, C, point) && hgui::kernel::distance(point, c) >= m_cornerAngularRadius)
		|| (hgui::point::is_in_rectangle(dp, d, D, point) && hgui::kernel::distance(point, d) >= m_cornerAngularRadius));
}

void hgui::kernel::Button::set_position(const point& newPosition)
{
	Widget::set_position(newPosition);
	m_modelMatrix = glm::mat4(1.0);
	m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(newPosition.x, newPosition.y, 0.0f));
	m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(0.5f * m_size.width, 0.5f * m_size.height, 0.0f));
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_angularRotation), glm::vec3(0.0f, 0.0f, 1.0f));
	m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(-0.5f * m_size.width, -0.5f * m_size.height, 0.0f));
	m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(m_size.width, m_size.height, 1.0f));
	if (m_text)
	{
		m_text->set_position(point(m_position + (m_size - m_text->get_size()) / 2));
	}
}

void hgui::kernel::Button::set_state(const state& state)
{
	m_state = state;
}

void hgui::kernel::Button::set_color(const color& newColor)
{
	m_color = newColor;
}

const hgui::state& hgui::kernel::Button::get_state() const
{
	return m_state;
}

void hgui::kernel::Button::set_textures(const std::shared_ptr<Texture>& texture)
{
	m_texture = texture;
}

void hgui::kernel::Button::init_data()
{
	std::vector<glm::vec4> vertices = {
		//Position																		//Texture Position
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