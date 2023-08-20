#include <hgui/header/Canva.h>

hgui::kernel::Canva::Canva(const std::shared_ptr<Shader>& shader, const size& size, const point& position, const color& color, float angularRotation) :
	Widget(shader, size, position, color), m_angularRoation(angularRotation), 
	m_drawer(std::make_shared<kernel::Drawer>(shader, position, size))
{
	set_position(position);
	init_data();
}

void hgui::kernel::Canva::draw() const
{
	int width, height;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
	m_shader->use().set_mat4("modelMatrix", m_modelMatrix)
		.set_mat4("projectionMatrix", glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.f, -1.0f, 1.0f));
	m_VAO->bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	m_VAO->unbind();
	m_shader->set_mat4("modelMatrix", glm::mat4(1.0));
	m_drawer->draw();
}

void hgui::kernel::Canva::set_position(const point& newPosition)
{
	Widget::set_position(newPosition);
	m_modelMatrix = glm::mat4(1.0);
	m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(newPosition.x, newPosition.y, 0.0f));
	m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(0.5f * m_size.width, 0.5f * m_size.height, 0.0f));
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_angularRoation), glm::vec3(0.0f, 0.0f, 1.0f));
	m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(-0.5f * m_size.width, -0.5f * m_size.height, 0.0f));
	m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(m_size.width / 4, m_size.height / 4, 1.0f));
	m_shader->use().set_vec2("canvaPosition", m_position)
		.set_vec2("canvaSize", m_size);
}

const std::shared_ptr<hgui::kernel::Drawer>& hgui::kernel::Canva::get_drawer() const
{
	return m_drawer;
}

void hgui::kernel::Canva::init_data()
{
	float vertices[] = {
		0.0f,  1.0f,  m_color.r, m_color.g, m_color.b,
		0.0f, 0.0f,  m_color.r, m_color.g, m_color.b,
		1.0f, 0.0f,  m_color.r, m_color.g, m_color.b,

		0.0f,  1.0f,  m_color.r, m_color.g, m_color.b,
		1.0f, 0.0f,  m_color.r, m_color.g, m_color.b,
		1.0f,  1.0f,  m_color.r, m_color.g, m_color.b,
	};
	m_VAO->bind();
	m_VBO->bind();
	m_VBO->set_data(vertices, sizeof(vertices));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	m_VAO->unbind();
}