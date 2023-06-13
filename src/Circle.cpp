#include <hgui/header/Circle.h>

hgui::kernel::shape::Circle::Circle(glm::vec2 centerPosition, float radius, glm::vec3 color, bool fill, float thickness) :
	Shape(fill, thickness, centerPosition)
{
	int segmentNumber = 100;
	float angleIncrement = 2.0f * glm::pi<float>() / segmentNumber;
	std::vector<float> vertices;
	for (int i = 0; i < segmentNumber; i++)
	{
		float angle = i * angleIncrement;
		float x = centerPosition.x + radius * std::cos(angle);
		float y = centerPosition.y + radius * std::sin(angle);
		std::vector<float> triangle = { x, y, color.r, color.g, color.b };
		vertices.insert(vertices.end(), triangle.begin(), triangle.end());
	}
	m_VAO->bind();
	m_VBO->bind();
	m_VBO->set_data(vertices.data(), static_cast<int>(vertices.size()) * sizeof(float));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	m_VAO->unbind();
}

void hgui::kernel::shape::Circle::draw(const std::shared_ptr<Shader>& shader) const
{
	if (m_fill)
	{
		m_VAO->bind();
		glDrawArrays(GL_TRIANGLE_FAN, 0, 100);
		m_VAO->unbind();
	}
	else
	{
		glEnable(GL_STENCIL_TEST);
		glClear(GL_STENCIL_BUFFER_BIT);

		glm::mat4 modelMatrix(1.0f);
		float scale = std::abs(1.0f - (m_thickness / 10.0f) / 2.0f);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(m_center - scale * m_center, 0.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
		glStencilMask(0xFF);
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		shader->use().set_mat4("modelMatrix", modelMatrix);
		m_VAO->bind();
		glDrawArrays(GL_TRIANGLE_FAN, 0, 100);
		m_VAO->unbind();
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

		modelMatrix = glm::mat4(1.0f);
		scale = std::abs(1.0f + (m_thickness / 10.0f) / 2.0f);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(m_center - scale * m_center, 0.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glStencilMask(0xFF);
		shader->use().set_mat4("modelMatrix", modelMatrix);
		m_VAO->bind();
		glDrawArrays(GL_TRIANGLE_FAN, 0, 100);
		m_VAO->unbind();
		glDisable(GL_STENCIL_TEST);
	}
}
