#include "../include/hgui/header/Circle.h"
#include "../include/hgui/header/Shader.h"
#include "../include/hgui/header/ShaderManager.h"
#include "../include/hgui/header/VertexArrayObject.h"
#include "../include/hgui/header/VertexBufferObject.h"
#include "../include/hgui/header/GLSL.h"

hgui::kernel::shape::Circle::Circle(const point& centerPosition, const float radius, const color& color, const bool fill, float thickness) :
	Shape(fill, thickness, color, std::make_pair(centerPosition, radius))
{
	if (!m_shader)
	{
		m_shader = ShaderManager::create(HGUI_GLSL_VERTEX_CIRCLE, HGUI_GLSL_FRAGMENT_CIRCLE);
	}
	if (fill)
		thickness = 0.0f;
	const float vertices[] = {
				centerPosition.x - radius - thickness, centerPosition.y - radius - thickness,
				centerPosition.x + radius + thickness, centerPosition.y - radius - thickness,
				centerPosition.x - radius - thickness, centerPosition.y + radius + thickness,
				centerPosition.x + radius + thickness, centerPosition.y + radius + thickness,
			};
	m_VAO->bind();
	m_VBO->bind();
	m_VBO->set_data(vertices, sizeof(vertices));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), static_cast<void*>(nullptr));
	m_VAO->unbind();
}

void hgui::kernel::shape::Circle::draw(const point& canvasPosition, const size& canvasSize) const
{
	int width, height;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
	const auto [center, radius] = std::get<std::pair<point, HGUI_PRECISION>>(m_data);
	m_shader->use().set_mat4("projectionMatrix", glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.f, -1.0f, 1.0f))
	        .set_vec2("canvasPosition", canvasPosition)
	        .set_vec2("canvasSize", canvasSize)
	        .set_vec2("center", center)
	        .set_vec4("color", m_color)
	        .set_float("radius", radius)
	        .set_float("thickness", m_thickness)
	        .set_int("fill", m_fill);
	m_VAO->bind();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	m_VAO->unbind();
}
