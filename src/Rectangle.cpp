#include <hgui/header/Rectangle.h>

std::shared_ptr<hgui::kernel::Shader> hgui::kernel::shape::Rectangle::m_shader(nullptr);

hgui::kernel::shape::Rectangle::Rectangle(const point& topLeftVertex, const point& bottomRightVertex, const color& color, const bool fill,
	const float thickness) : Shape(fill, thickness, color, std::make_pair(topLeftVertex, bottomRightVertex))
{
	if (!m_shader)
	{
		m_shader = ShaderManager::create(
			R"(
				#version 330 core

				layout (location = 0) in vec2 vertex;

				uniform mat4 projectionMatrix;

				void main()
				{
					gl_Position = projectionMatrix * vec4(vertex, 0.0, 1.0);
				}
			)",
			R"(
				#version 330 core

				layout(origin_upper_left, pixel_center_integer) in vec4 gl_FragCoord;


				out vec4 fragmentColor;

				uniform vec2 canvasPosition;
				uniform vec2 canvasSize;
				uniform vec2 center;
				uniform vec3 color;
				uniform float radius;
				uniform bool circle;

				void main()
				{
				    vec2 pixelCoords = gl_FragCoord.xy;

				    if (pixelCoords.x < canvasPosition.x || pixelCoords.x >= canvasPosition.x + canvasSize.x ||
				        pixelCoords.y < canvasPosition.y || pixelCoords.y >= canvasPosition.y + canvasSize.y ||
						(circle && distance(pixelCoords, center) > radius))
				    {
				        discard;
				    } 
					fragmentColor = vec4(color, 1.0);
				} 
			)"
		);
	}
	hgui::point firstVertex = topLeftVertex,
		secondVertex = hgui::point(bottomRightVertex.x, topLeftVertex.y),
		thirdVertex = bottomRightVertex,
		fourthVertex = hgui::point(topLeftVertex.x, bottomRightVertex.y);
	if (fill)
	{
		const float vertices[] = {
			secondVertex.x, secondVertex.y,
			firstVertex.x, firstVertex.y,
			thirdVertex.x, thirdVertex.y,
			fourthVertex.x, fourthVertex.y
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
		vertices.reserve(96);
		// First Line
		hgui::point v = secondVertex - firstVertex;
		hgui::point n(-v.y, v.x); n.normalize();
		hgui::point corner1 = firstVertex - n * halfThickness,
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
		n = hgui::point(-v.y, v.x); n.normalize();
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
		v = fourthVertex - thirdVertex;
		n = hgui::point(-v.y, v.x); n.normalize();
		corner1 = thirdVertex - n * halfThickness;
		corner2 = thirdVertex + n * halfThickness;
		corner3 = fourthVertex + n * halfThickness;
		corner4 = fourthVertex - n * halfThickness;
		vertices.insert(vertices.end(),
			{
				thirdVertex.x - halfThickness, thirdVertex.y - halfThickness,
				thirdVertex.x + halfThickness, thirdVertex.y - halfThickness,
				thirdVertex.x - halfThickness, thirdVertex.y + halfThickness,
				thirdVertex.x + halfThickness, thirdVertex.y + halfThickness,

				fourthVertex.x - halfThickness, fourthVertex.y - halfThickness,
				fourthVertex.x + halfThickness, fourthVertex.y - halfThickness,
				fourthVertex.x - halfThickness, fourthVertex.y + halfThickness,
				fourthVertex.x + halfThickness, fourthVertex.y + halfThickness,

				corner2.x, corner2.y,
				corner1.x, corner1.y,
				corner3.x, corner3.y,
				corner4.x, corner4.y
			});
		// Fourth Line
		v = firstVertex - fourthVertex;
		n = hgui::point(-v.y, v.x); n.normalize();
		corner1 = fourthVertex - n * halfThickness;
		corner2 = fourthVertex + n * halfThickness;
		corner3 = firstVertex + n * halfThickness;
		corner4 = firstVertex - n * halfThickness;
		vertices.insert(vertices.end(),
			{
				fourthVertex.x - halfThickness, fourthVertex.y - halfThickness,
				fourthVertex.x + halfThickness, fourthVertex.y - halfThickness,
				fourthVertex.x - halfThickness, fourthVertex.y + halfThickness,
				fourthVertex.x + halfThickness, fourthVertex.y + halfThickness,

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
		m_VBO->set_data(vertices.data(), static_cast<int>(vertices.size())* static_cast<int>(sizeof(float)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), static_cast<void*>(nullptr));
		m_VAO->unbind();
	}
}

void hgui::kernel::shape::Rectangle::draw(const hgui::point& canvasPosition, const hgui::size& canvasSize) const
{
	int width, height;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
	const auto& [topLeftVertex, bottomRightVertex] = std::get<std::pair<hgui::point, hgui::point>>(m_data);
	const hgui::point firstVertex = topLeftVertex,
		secondVertex = hgui::point(bottomRightVertex.x, topLeftVertex.y),
		thirdVertex = bottomRightVertex,
		fourthVertex = hgui::point(topLeftVertex.x, bottomRightVertex.y);
	m_shader->use().set_mat4("projectionMatrix", glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.f, -1.0f, 1.0f))
		.set_vec2("canvasPosition", canvasPosition)
		.set_vec2("canvasSize", canvasSize)
		.set_vec3("color", static_cast<hgui::kernel::Vector<HGUI_PRECISION, 3>>(m_color))
		.set_float("radius", m_thickness / 2.0f);
	m_VAO->bind();
	if (m_fill)
	{
		m_shader->set_int("circle", 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	else
	{
		m_shader->set_int("circle", 1);
		m_shader->set_vec2("center", firstVertex);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		m_shader->set_vec2("center", secondVertex);
		glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
		m_shader->set_int("circle", 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);

		m_shader->set_int("circle", 1);
		m_shader->set_vec2("center", secondVertex);
		glDrawArrays(GL_TRIANGLE_STRIP, 12, 4);
		m_shader->set_vec2("center", thirdVertex);
		glDrawArrays(GL_TRIANGLE_STRIP, 16, 4);
		m_shader->set_int("circle", 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 20, 4);

		m_shader->set_int("circle", 1);
		m_shader->set_vec2("center", thirdVertex);
		glDrawArrays(GL_TRIANGLE_STRIP, 24, 4);
		m_shader->set_vec2("center", fourthVertex);
		glDrawArrays(GL_TRIANGLE_STRIP, 28, 4);
		m_shader->set_int("circle", 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 32, 4);

		m_shader->set_int("circle", 1);
		m_shader->set_vec2("center", fourthVertex);
		glDrawArrays(GL_TRIANGLE_STRIP, 36, 4);
		m_shader->set_vec2("center", firstVertex);
		glDrawArrays(GL_TRIANGLE_STRIP, 40, 4);
		m_shader->set_int("circle", 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 44, 4);
	}
	m_VAO->unbind();
}
