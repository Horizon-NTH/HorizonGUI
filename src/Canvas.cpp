#include "../include/hgui/header/Canvas.h"
#include "../include/hgui/header/Drawer.h"
#include "../include/hgui/header/Shader.h"
#include "../include/hgui/header/VertexArrayObject.h"
#include "../include/hgui/header/VertexBufferObject.h"

hgui::kernel::Canvas::Canvas(const std::shared_ptr<Shader>& shader, const size& size, const point& position, const color& color) :
	Widget(shader, size, position),
	m_modelMatrix(),
	m_drawer(std::make_shared<Drawer>(position, size)),
	m_color(color)
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
	m_modelMatrix = scale(m_modelMatrix, glm::vec3(m_size.width, m_size.height, 1.0f));
	m_drawer->m_position = newPosition;
}

void hgui::kernel::Canvas::set_size(const size& newSize)
{
	Widget::set_size(newSize);
	m_drawer->m_size = m_size;
}

bool hgui::kernel::Canvas::is_inside(const point& point) const
{
	return point::is_in_rectangle(m_position, hgui::point(m_position.x + m_size.width, m_position.y), hgui::point(m_position.x, m_position.y + m_size.height), point);
}

const std::shared_ptr<hgui::kernel::Drawer>& hgui::kernel::Canvas::get_drawer() const
{
	return m_drawer;
}

void hgui::kernel::Canvas::init_data() const
{
	const float vertices[] = {
				0.0f, 1.0f, m_color.r, m_color.g, m_color.b, m_color.a,
				0.0f, 0.0f, m_color.r, m_color.g, m_color.b, m_color.a,
				1.0f, 0.0f, m_color.r, m_color.g, m_color.b, m_color.a,

				0.0f, 1.0f, m_color.r, m_color.g, m_color.b, m_color.a,
				1.0f, 0.0f, m_color.r, m_color.g, m_color.b, m_color.a,
				1.0f, 1.0f, m_color.r, m_color.g, m_color.b, m_color.a
			};
	m_VAO->bind();
	m_VBO->bind();
	m_VBO->set_data(vertices, sizeof(vertices));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
	m_VAO->unbind();
}
