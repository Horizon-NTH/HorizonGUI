#include "../include/hgui/header/StraightLine.h"
#include "../include/hgui/header/ShaderManager.h"
#include "../include/hgui/header/Shader.h"
#include "../include/hgui/header/VertexArrayObject.h"
#include "../include/hgui/header/VertexBufferObject.h"
#include "../include/hgui/header/GLSL.h"

hgui::kernel::shape::StraightLine::StraightLine(const point& firstVertex, const point& secondVertex, const color& color, const float thickness) :
	Shape(true, thickness, color, std::make_tuple(firstVertex, secondVertex, thickness))
{
	if (!m_shader)
	{
		m_shader = ShaderManager::create(HGUI_GLSL_VERTEX_RECTANGLE, HGUI_GLSL_FRAGMENT_RECTANGLE);
	}
	float halfThickness = thickness / 2.0f;
	point v = secondVertex - firstVertex;
	point n(-v.y, v.x);
	n = point::normalize(n);
	point corner1 = firstVertex - n * halfThickness,
			corner2 = firstVertex + n * halfThickness,
			corner3 = secondVertex + n * halfThickness,
			corner4 = secondVertex - n * halfThickness;
	const float vertices[] =
			{
				firstVertex.x - halfThickness, firstVertex.y - halfThickness,
				firstVertex.x + halfThickness, firstVertex.y - halfThickness,
				firstVertex.x - halfThickness, firstVertex.y + halfThickness,
				firstVertex.x + halfThickness, firstVertex.y + halfThickness,

				secondVertex.x - halfThickness, secondVertex.y - halfThickness,
				secondVertex.x + halfThickness, secondVertex.y - halfThickness,
				secondVertex.x - halfThickness, secondVertex.y + halfThickness,
				secondVertex.x + halfThickness, secondVertex.y + halfThickness,

				corner2.x, corner2.y,
				corner1.x, corner1.y,
				corner3.x, corner3.y,
				corner4.x, corner4.y
			};

	m_VAO->bind();
	m_VBO->bind();
	m_VBO->set_data(vertices, sizeof(vertices));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), static_cast<void*>(nullptr));
	m_VAO->unbind();
}

void hgui::kernel::shape::StraightLine::draw(const point& canvasPosition, const size& canvasSize) const
{
	int width, height;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
	const auto& [P1, P2, thickness] = std::get<std::tuple<point, point, HGUI_PRECISION>>(m_data);
	m_shader->use().set_mat4("projectionMatrix", glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.f, -1.0f, 1.0f))
	        .set_vec2("canvasPosition", canvasPosition)
	        .set_vec2("canvasSize", canvasSize)
	        .set_vec4("color", m_color)
	        .set_float("radius", m_thickness / 2.0f);
	m_VAO->bind();
	m_shader->set_int("circle", 1);
	m_shader->set_vec2("center", P1);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	m_shader->set_vec2("center", P2);
	glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
	m_shader->set_int("circle", 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);
	m_VAO->unbind();
}
