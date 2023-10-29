#include <hgui/header/StraightLine.h>

hgui::kernel::shape::StraightLine::StraightLine(const point& firstVertex, const point& secondVertex, const color& color,
                                                const float thickness) : Shape(true, thickness)
{
	const float vertices[] = {
				firstVertex.x, firstVertex.y, color.r, color.g, color.b,
				secondVertex.x, secondVertex.y, color.r, color.g, color.b
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

void hgui::kernel::shape::StraightLine::draw(const std::shared_ptr<Shader>& shader) const
{
	shader->use();
	m_VAO->bind();
	glLineWidth(m_thickness);
	glDrawArrays(GL_LINES, 0, 2);
	glLineWidth(1.0f);
	m_VAO->unbind();
}
