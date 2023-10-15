#include <hgui/header/Button.h>

hgui::kernel::Button::Button(const std::function<void()>& function, const std::shared_ptr<Shader>& shader, const size& size, const point& position, const std::shared_ptr<Label>& text, const color& color, float angularRotation, float cornerAngularRadius, const std::shared_ptr<Texture>& texture) :
	Widget(shader, size, position, color), m_function(function), m_angularRoation(angularRotation), 
	m_cornerAngularRadius(cornerAngularRadius), m_state(state::NORMAL), m_modelMatrix(1.0),
	m_text(text)
{
	set_textures(texture);
	set_position(position);
	init_data();
	if (m_text)
	{
		m_text->set_width(static_cast<unsigned int>(std::max(m_size.width / 2, m_size.width - m_cornerAngularRadius)));
		if (m_text->get_size().height > m_size.height - m_cornerAngularRadius)
		{
			m_text->set_height(static_cast<unsigned int>(std::max(m_size.height / 2, m_size.height - m_cornerAngularRadius)));
		}
		m_text->set_position(m_position + (m_size - m_text->get_size()) / 2);
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
		.set_vec4("buttonColor", m_color).set_int("focused", static_cast<int>(m_state))
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

void hgui::kernel::Button::set_position(const point& newPosition)
{
	Widget::set_position(newPosition);
	m_modelMatrix = glm::mat4(1.0);
	m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(newPosition.x, newPosition.y, 0.0f));
	m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(0.5f * m_size.width, 0.5f * m_size.height, 0.0f));
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_angularRoation), glm::vec3(0.0f, 0.0f, 1.0f));
	m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(-0.5f * m_size.width, -0.5f * m_size.height, 0.0f));
	m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(m_size.width, m_size.height, 1.0f));
	if (m_text)
	{
		m_text->set_position(m_position + (m_size - m_text->get_size()) / 2);
	}
}

void hgui::kernel::Button::set_state(const state& state)
{
	m_state = state;
}

void hgui::kernel::Button::set_textures(const std::shared_ptr<Texture>& texture)
{
	m_texture = texture;
}

void hgui::kernel::Button::init_data()
{
	std::vector<glm::vec4> vertices = {
		//Position																		//Texture Position
		{m_cornerAngularRadius, 0.0f, 													m_cornerAngularRadius, 0.0f},
		{m_cornerAngularRadius, m_cornerAngularRadius,									m_cornerAngularRadius, m_cornerAngularRadius},
		{m_size.width - m_cornerAngularRadius, m_cornerAngularRadius,					m_size.width - m_cornerAngularRadius, m_cornerAngularRadius},

		{m_cornerAngularRadius, 0.0f, 													m_cornerAngularRadius, 0.0f},
		{m_size.width - m_cornerAngularRadius, 0.0f,									m_size.width - m_cornerAngularRadius, 0.0f},
		{m_size.width - m_cornerAngularRadius, m_cornerAngularRadius,					m_size.width - m_cornerAngularRadius, m_cornerAngularRadius},


		{0.0f, m_cornerAngularRadius,													0.0f, m_cornerAngularRadius},
		{0.0f, m_size.height - m_cornerAngularRadius,									0.0f, m_size.height - m_cornerAngularRadius},
		{m_size.width, m_size.height - m_cornerAngularRadius,							m_size.width, m_size.height - m_cornerAngularRadius},

		{0.0f, m_cornerAngularRadius,													0.0f, m_cornerAngularRadius},
		{m_size.width, m_cornerAngularRadius,											m_size.width, m_cornerAngularRadius},
		{m_size.width, m_size.height - m_cornerAngularRadius,							m_size.width, m_size.height - m_cornerAngularRadius},


		{m_cornerAngularRadius, m_size.height - m_cornerAngularRadius,					m_cornerAngularRadius, m_size.height - m_cornerAngularRadius},
		{m_cornerAngularRadius, m_size.height,											m_cornerAngularRadius, m_size.height},
		{m_size.width - m_cornerAngularRadius, m_size.height,							m_size.width - m_cornerAngularRadius, m_size.height},

		{m_cornerAngularRadius, m_size.height - m_cornerAngularRadius,					m_cornerAngularRadius, m_size.height - m_cornerAngularRadius},
		{m_size.width - m_cornerAngularRadius, m_size.height - m_cornerAngularRadius,	m_size.width - m_cornerAngularRadius, m_size.height - m_cornerAngularRadius},
		{m_size.width - m_cornerAngularRadius, m_size.height,							m_size.width - m_cornerAngularRadius, m_size.height},
	};
	int numSegments = 10;
	float angle;
	for (int i = 0; i < numSegments; i++)
	{
		angle = i * glm::pi<float>() / (2 * numSegments);
		vertices.push_back(glm::vec4(m_cornerAngularRadius - m_cornerAngularRadius * cos(angle), m_cornerAngularRadius - m_cornerAngularRadius * sin(angle), m_cornerAngularRadius - m_cornerAngularRadius * cos(angle), m_cornerAngularRadius - m_cornerAngularRadius * sin(angle)));
		angle = (i + 1) * glm::pi<float>() / (2 * numSegments);
		vertices.push_back(glm::vec4(m_cornerAngularRadius - m_cornerAngularRadius * cos(angle), m_cornerAngularRadius - m_cornerAngularRadius * sin(angle), m_cornerAngularRadius - m_cornerAngularRadius * cos(angle), m_cornerAngularRadius - m_cornerAngularRadius * sin(angle)));
		vertices.push_back(glm::vec4(0.f + m_cornerAngularRadius, 0.0f + m_cornerAngularRadius, 0.f + m_cornerAngularRadius, 0.0f + m_cornerAngularRadius));
	}
	for (int i = 0; i < numSegments; i++)
	{
		angle = i * glm::pi<float>() / (2 * numSegments);
		vertices.push_back(glm::vec4(m_size.width - m_cornerAngularRadius + m_cornerAngularRadius * cos(angle), m_cornerAngularRadius - m_cornerAngularRadius * sin(angle), m_size.width - m_cornerAngularRadius + m_cornerAngularRadius * cos(angle), m_cornerAngularRadius - m_cornerAngularRadius * sin(angle)));
		angle = (i + 1) * glm::pi<float>() / (2 * numSegments);
		vertices.push_back(glm::vec4(m_size.width - m_cornerAngularRadius + m_cornerAngularRadius * cos(angle), m_cornerAngularRadius - m_cornerAngularRadius * sin(angle), m_size.width - m_cornerAngularRadius + m_cornerAngularRadius * cos(angle), m_cornerAngularRadius - m_cornerAngularRadius * sin(angle)));
		vertices.push_back(glm::vec4(m_size.width - m_cornerAngularRadius, 0.0f + m_cornerAngularRadius, m_size.width - m_cornerAngularRadius, 0.0f + m_cornerAngularRadius));
	}
	for (int i = 0; i < numSegments; i++)
	{
		angle = i * glm::pi<float>() / (2 * numSegments);
		vertices.push_back(glm::vec4(m_size.width - m_cornerAngularRadius + m_cornerAngularRadius * cos(angle), m_size.height - m_cornerAngularRadius + m_cornerAngularRadius * sin(angle), m_size.width - m_cornerAngularRadius + m_cornerAngularRadius * cos(angle), m_size.height - m_cornerAngularRadius + m_cornerAngularRadius * sin(angle)));
		angle = (i + 1) * glm::pi<float>() / (2 * numSegments);
		vertices.push_back(glm::vec4(m_size.width - m_cornerAngularRadius + m_cornerAngularRadius * cos(angle), m_size.height - m_cornerAngularRadius + m_cornerAngularRadius * sin(angle), m_size.width - m_cornerAngularRadius + m_cornerAngularRadius * cos(angle), m_size.height - m_cornerAngularRadius + m_cornerAngularRadius * sin(angle)));
		vertices.push_back(glm::vec4(m_size.width - m_cornerAngularRadius, m_size.height - m_cornerAngularRadius, m_size.width - m_cornerAngularRadius, m_size.height - m_cornerAngularRadius));
	}
	for (int i = 0; i < numSegments; i++)
	{
		angle = i * glm::pi<float>() / (2 * numSegments);
		vertices.push_back(glm::vec4(m_cornerAngularRadius - m_cornerAngularRadius * cos(angle), m_size.height - m_cornerAngularRadius + m_cornerAngularRadius * sin(angle), m_cornerAngularRadius - m_cornerAngularRadius * cos(angle), m_size.height - m_cornerAngularRadius + m_cornerAngularRadius * sin(angle)));
		angle = (i + 1) * glm::pi<float>() / (2 * numSegments);
		vertices.push_back(glm::vec4(m_cornerAngularRadius - m_cornerAngularRadius * cos(angle), m_size.height - m_cornerAngularRadius + m_cornerAngularRadius * sin(angle), m_cornerAngularRadius - m_cornerAngularRadius * cos(angle), m_size.height - m_cornerAngularRadius + m_cornerAngularRadius * sin(angle)));
		vertices.push_back(glm::vec4(0.0f + m_cornerAngularRadius, m_size.height - m_cornerAngularRadius, 0.0f + m_cornerAngularRadius, m_size.height - m_cornerAngularRadius));
	}
	glm::mat4 normalize = {
		1.0f / m_size.width,	0.0f,						0.0f,					0.0f,
		0.0f,					1.0 / m_size.height,		0.0f,					0.0f,
		0.0f,					0.0f,						1.0f / m_size.width,	0.0f,
		0.0f,					0.0f,						0.0f,					1.0f / m_size.height
	};
	for (auto& v : vertices)
	{
		v = normalize * v;
	}
	m_VAO->bind();
	m_VBO->bind();
	m_VBO->set_data(vertices.data(), static_cast<int>(vertices.size()) * sizeof(glm::vec4));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
	m_VAO->unbind();
}
