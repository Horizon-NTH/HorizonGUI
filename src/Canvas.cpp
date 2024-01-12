#include "../include/hgui/header/Canvas.h"

hgui::kernel::Canvas::Canvas(const std::shared_ptr<Shader>& shader, const size& size, const point& position, const color& color, const HGUI_PRECISION angularRotation) :
	Widget(shader, size, position, color, angularRotation),
	m_drawer(std::make_shared<Drawer>(position, size, m_angularRotation))
{
	Canvas::set_position(position);
	init_data();
}

void hgui::kernel::Canvas::draw() const
{
	int width, height;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
	m_shader->use().set_mat4("modelMatrix", m_modelMatrix)
	        .set_mat4("projectionMatrix", glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.f, -1.0f, 1.0f));
	m_VAO->bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	m_VAO->unbind();
	m_drawer->draw();
}

void hgui::kernel::Canvas::set_position(const point& newPosition)
{
	Widget::set_position(newPosition);
	m_modelMatrix = glm::mat4(1.0);
	m_modelMatrix = translate(m_modelMatrix, glm::vec3(m_position.x, m_position.y, 0.0f));
	m_modelMatrix = translate(m_modelMatrix, glm::vec3(0.5f * m_size.width, 0.5f * m_size.height, 0.0f));
	m_modelMatrix = rotate(m_modelMatrix, glm::radians(m_angularRotation), glm::vec3(0.0f, 0.0f, 1.0f));
	m_modelMatrix = translate(m_modelMatrix, glm::vec3(-0.5f * m_size.width, -0.5f * m_size.height, 0.0f));
	m_modelMatrix = scale(m_modelMatrix, glm::vec3(m_size.width, m_size.height, 1.0f));
	m_drawer->m_position = newPosition;
}

void hgui::kernel::Canvas::set_size(const size& newSize)
{
	Widget::set_size(newSize);
	m_drawer->m_size = m_size;
}

void hgui::kernel::Canvas::set_rotation(const float newAngularRotation)
{
	Widget::set_rotation(newAngularRotation);
	m_drawer->m_rotation = m_angularRotation;
}

bool hgui::kernel::Canvas::is_inside(const point& point) const
{
	const hgui::point center(m_position.x + m_size.width / 2.f, m_position.y + m_size.height / 2.f);
	const auto A = point::rotate(hgui::point(m_position.x, m_position.y), center, m_angularRotation),
			B = point::rotate(hgui::point(m_position.x + m_size.width, m_position.y), center, m_angularRotation),
			C = point::rotate(hgui::point(m_position.x + m_size.width, m_position.y + m_size.height), center, m_angularRotation),
			D = point::rotate(hgui::point(m_position.x, m_position.y + m_size.height), center, m_angularRotation);

	return point::is_in_rectangle(A, B, D, point);
}

const std::shared_ptr<hgui::kernel::Drawer>& hgui::kernel::Canvas::get_drawer() const
{
	return m_drawer;
}

void hgui::kernel::Canvas::init_data() const
{
	const float vertices[] = {
				0.0f, 1.0f, m_color.r, m_color.g, m_color.b,
				0.0f, 0.0f, m_color.r, m_color.g, m_color.b,
				1.0f, 0.0f, m_color.r, m_color.g, m_color.b,

				0.0f, 1.0f, m_color.r, m_color.g, m_color.b,
				1.0f, 0.0f, m_color.r, m_color.g, m_color.b,
				1.0f, 1.0f, m_color.r, m_color.g, m_color.b,
			};
	m_VAO->bind();
	m_VBO->bind();
	m_VBO->set_data(vertices, sizeof(vertices));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
	m_VAO->unbind();
}
