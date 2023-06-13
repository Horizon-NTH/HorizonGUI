#include <hgui/header/StraightLine.h>

hgui::kernel::shape::StraightLine::StraightLine(glm::vec2 firstVertex, glm::vec2 secondVertex, glm::vec3 color, float thickness) :
	Shape(true, thickness)
{
	float vertices[] = {
		firstVertex.x, firstVertex.y,  color.r, color.g, color.b,
		secondVertex.x, secondVertex.y,  color.r, color.g, color.b
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

void hgui::kernel::shape::StraightLine::draw(const std::shared_ptr<Shader>& shader) const
{
	shader->use();
	m_VAO->bind();
	glLineWidth(m_thickness);
	glDrawArrays(GL_LINES, 0, 2);
	glLineWidth(1.0f);
	m_VAO->unbind();
}
