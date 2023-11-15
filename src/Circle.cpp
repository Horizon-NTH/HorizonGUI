#include <hgui/header/Circle.h>

hgui::kernel::shape::Circle::Circle(const point& centerPosition, const float radius, const color& color, const bool fill,
                                    const float thickness) : Shape(fill, thickness, std::make_pair(centerPosition, radius))
{
	constexpr int segmentNumber = 100;
	constexpr float angleIncrement = 2.0f * glm::pi<float>() / segmentNumber;
	std::vector<float> vertices;
	for (int i = 0; i < segmentNumber; i++)
	{
		const float angle = static_cast<float>(i) * angleIncrement;
		const float x = centerPosition.x + radius * std::cos(angle);
		const float y = centerPosition.y + radius * std::sin(angle);
		std::vector<float> triangle = {x, y, color.r, color.g, color.b};
		vertices.insert(vertices.end(), triangle.begin(), triangle.end());
	}
	m_VAO->bind();
	m_VBO->bind();
	m_VBO->set_data(vertices.data(), static_cast<int>(vertices.size()) * static_cast<int>(sizeof(float)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
	m_VAO->unbind();
}

void hgui::kernel::shape::Circle::draw(const std::pair<std::shared_ptr<Shader>, std::shared_ptr<Shader>>& shaders) const
{
	if (m_fill)
	{
		shaders.second->use();
		m_VAO->bind();
		glDrawArrays(GL_TRIANGLE_FAN, 0, 100);
		m_VAO->unbind();
	}
	else
	{
		
	}
}
