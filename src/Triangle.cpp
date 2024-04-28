#include "../include/hgui/header/Triangle.h"
#include "../include/hgui/header/Shader.h"
#include "../include/hgui/header/ShaderManager.h"
#include "../include/hgui/header/VertexArrayObject.h"
#include "../include/hgui/header/VertexBufferObject.h"
#include "../include/hgui/header/GLSL.h"

hgui::kernel::shape::Triangle::Triangle(const point& firstVertex, const point& secondVertex, const point& thirdVertex, const color& color, const bool fill, const float thickness) :
	Shape(fill, thickness, color, std::array{firstVertex, secondVertex, thirdVertex})
{
	if (!m_shader)
	{
		m_shader = ShaderManager::create(HGUI_GLSL_VERTEX_RECTANGLE, HGUI_GLSL_FRAGMENT_RECTANGLE);
	}
	if (fill)
	{
		const float vertices[] = {
					firstVertex.x, firstVertex.y,
					secondVertex.x, secondVertex.y,
					thirdVertex.x, thirdVertex.y,
				};
		m_VAO->bind();
		m_VBO->bind();
		m_VBO->set_data(vertices, sizeof(vertices));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), static_cast<void*>(nullptr));
		m_VAO->unbind();
	}
	else
	{
		float halfThickness = thickness / 2.0f;
		std::vector<float> vertices;
		vertices.reserve(72);
		// First Line
		point v = secondVertex - firstVertex;
		point n(-v.y, v.x);
		n = point::normalize(n);
		point corner1 = firstVertex - n * halfThickness,
				corner2 = firstVertex + n * halfThickness,
				corner3 = secondVertex + n * halfThickness,
				corner4 = secondVertex - n * halfThickness;
		vertices.insert(vertices.end(),
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
			});
		// Second Line
		v = thirdVertex - secondVertex;
		n = point(-v.y, v.x);
		n = point::normalize(n);
		corner1 = secondVertex - n * halfThickness;
		corner2 = secondVertex + n * halfThickness;
		corner3 = thirdVertex + n * halfThickness;
		corner4 = thirdVertex - n * halfThickness;
		vertices.insert(vertices.end(),
			{
				secondVertex.x - halfThickness, secondVertex.y - halfThickness,
				secondVertex.x + halfThickness, secondVertex.y - halfThickness,
				secondVertex.x - halfThickness, secondVertex.y + halfThickness,
				secondVertex.x + halfThickness, secondVertex.y + halfThickness,

				thirdVertex.x - halfThickness, thirdVertex.y - halfThickness,
				thirdVertex.x + halfThickness, thirdVertex.y - halfThickness,
				thirdVertex.x - halfThickness, thirdVertex.y + halfThickness,
				thirdVertex.x + halfThickness, thirdVertex.y + halfThickness,

				corner2.x, corner2.y,
				corner1.x, corner1.y,
				corner3.x, corner3.y,
				corner4.x, corner4.y
			});
		// Third Line
		v = firstVertex - thirdVertex;
		n = point(-v.y, v.x);
		n = point::normalize(n);
		corner1 = thirdVertex - n * halfThickness;
		corner2 = thirdVertex + n * halfThickness;
		corner3 = firstVertex + n * halfThickness;
		corner4 = firstVertex - n * halfThickness;
		vertices.insert(vertices.end(),
			{
				thirdVertex.x - halfThickness, thirdVertex.y - halfThickness,
				thirdVertex.x + halfThickness, thirdVertex.y - halfThickness,
				thirdVertex.x - halfThickness, thirdVertex.y + halfThickness,
				thirdVertex.x + halfThickness, thirdVertex.y + halfThickness,

				firstVertex.x - halfThickness, firstVertex.y - halfThickness,
				firstVertex.x + halfThickness, firstVertex.y - halfThickness,
				firstVertex.x - halfThickness, firstVertex.y + halfThickness,
				firstVertex.x + halfThickness, firstVertex.y + halfThickness,

				corner2.x, corner2.y,
				corner1.x, corner1.y,
				corner3.x, corner3.y,
				corner4.x, corner4.y
			});

		m_VAO->bind();
		m_VBO->bind();
		m_VBO->set_data(vertices.data(), static_cast<int>(vertices.size()) * static_cast<int>(sizeof(float)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), static_cast<void*>(nullptr));
		m_VAO->unbind();
	}
}

void hgui::kernel::shape::Triangle::draw(const point& canvasPosition, const size& canvasSize) const
{
	int width, height;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
	const auto points = std::get<std::array<point, 3>>(m_data);
	m_shader->use().set_mat4("projectionMatrix", glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.f, -1.0f, 1.0f))
	        .set_vec2("canvasPosition", canvasPosition)
	        .set_vec2("canvasSize", canvasSize)
	        .set_vec4("color", m_color)
	        .set_float("radius", m_thickness / 2.0f);
	m_VAO->bind();
	if (m_fill)
	{
		m_shader->set_int("circle", 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	else
	{
		m_shader->set_int("circle", 1);
		m_shader->set_vec2("center", points[0]);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		m_shader->set_vec2("center", points[1]);
		glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
		m_shader->set_int("circle", 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);

		m_shader->set_int("circle", 1);
		m_shader->set_vec2("center", points[1]);
		glDrawArrays(GL_TRIANGLE_STRIP, 12, 4);
		m_shader->set_vec2("center", points[2]);
		glDrawArrays(GL_TRIANGLE_STRIP, 16, 4);
		m_shader->set_int("circle", 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 20, 4);

		m_shader->set_int("circle", 1);
		m_shader->set_vec2("center", points[2]);
		glDrawArrays(GL_TRIANGLE_STRIP, 24, 4);
		m_shader->set_vec2("center", points[0]);
		glDrawArrays(GL_TRIANGLE_STRIP, 28, 4);
		m_shader->set_int("circle", 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 32, 4);
	}
	m_VAO->unbind();
}
