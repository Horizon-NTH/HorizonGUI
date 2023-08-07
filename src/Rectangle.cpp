#include <hgui/header/Rectangle.h>

hgui::kernel::shape::Rectangle::Rectangle(const point& topLeftVertex, const point& bottomRightVertex, const color& color, bool fill, float thickness) :
	Shape(fill, thickness, (topLeftVertex + bottomRightVertex) / 2.0f)
{
	float vertices[] = {
		topLeftVertex.x, topLeftVertex.y,  color.r, color.g, color.b,
		topLeftVertex.x, bottomRightVertex.y,  color.r, color.g, color.b,
		bottomRightVertex.x, topLeftVertex.y,  color.r, color.g, color.b,

		bottomRightVertex.x, bottomRightVertex.y,  color.r, color.g, color.b,
		bottomRightVertex.x, topLeftVertex.y,  color.r, color.g, color.b,
		topLeftVertex.x, bottomRightVertex.y,  color.r, color.g, color.b
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

void hgui::kernel::shape::Rectangle::draw(const std::shared_ptr<Shader>& shader) const
{
	if (m_fill)
	{
		shader->use();
		m_VAO->bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		m_VAO->unbind();
	}
	else
	{
		glEnable(GL_STENCIL_TEST);
		glClear(GL_STENCIL_BUFFER_BIT);

		glm::mat4 modelMatrix(1.0f);
		float scale = std::abs(1.0f - (m_thickness / 10.0f) / 2.0f);
		point p = m_center - scale * m_center;
		modelMatrix = glm::translate(modelMatrix, glm::vec3(p.x, p.y, 0.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
		glStencilMask(0xFF);
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		shader->use().set_mat4("modelMatrix", modelMatrix);
		m_VAO->bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		m_VAO->unbind();
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

		modelMatrix = glm::mat4(1.0f);
		scale = std::abs(1.0f + (m_thickness / 10.0f) / 2.0f);
		point q = m_center - scale * m_center;
		modelMatrix = glm::translate(modelMatrix, glm::vec3(q.x, q.y, 0.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glStencilMask(0xFF);
		shader->use().set_mat4("modelMatrix", modelMatrix);
		m_VAO->bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		m_VAO->unbind();
		glDisable(GL_STENCIL_TEST);
	}
}
