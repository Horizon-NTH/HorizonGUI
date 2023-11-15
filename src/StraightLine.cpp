#include <hgui/header/StraightLine.h>

hgui::kernel::shape::StraightLine::StraightLine(const point& firstVertex, const point& secondVertex, const color& color,
                                                const float thickness) : Shape(true, thickness, std::make_tuple(firstVertex, secondVertex, thickness))
{
	const float vertices[] = {
				firstVertex.x, firstVertex.y, color.r, color.g, color.b, thickness,
				secondVertex.x, secondVertex.y, color.r, color.g, color.b, thickness
			};
	m_VAO->bind();
	m_VBO->bind();
	m_VBO->set_data(vertices, sizeof(vertices));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(5 * sizeof(float)));
	m_VAO->unbind();
}

void hgui::kernel::shape::StraightLine::draw(const std::pair<std::shared_ptr<Shader>, std::shared_ptr<Shader>>& shaders) const
{
	int width, height;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
	shaders.first->use().set_mat4("modelMatrix", glm::mat4(1.0))
		.set_mat4("projectionMatrix", glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.f, -1.0f, 1.0f));
	m_VAO->bind();
	glDrawArrays(GL_LINES, 0, 2);
	m_VAO->unbind();
}
