#include <hgui/header/StraightLine.h>

std::shared_ptr<hgui::kernel::Shader> hgui::kernel::shape::StraightLine::m_shader(nullptr);

hgui::kernel::shape::StraightLine::StraightLine(const point& firstVertex, const point& secondVertex, const color& color,
	const float thickness) : Shape(true, thickness, color, std::make_tuple(firstVertex, secondVertex, thickness))
{
	float halfThickness = thickness / 2.0f;
	hgui::point v = secondVertex - firstVertex;
	hgui::point n(-v.y, v.x); n.normalize();
	hgui::point corner1 = firstVertex - n * halfThickness,
		corner2 = firstVertex + n * halfThickness,
		corner3 = secondVertex + n * halfThickness,
		corner4 = secondVertex - n * halfThickness;
	const float vertices[] = {
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
}

void hgui::kernel::shape::StraightLine::draw(const hgui::point& canvasPosition, const hgui::size& canvasSize) const
{
	int width, height;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
	const auto& [P1, P2, thickness] = std::get<std::tuple<hgui::point, hgui::point, HGUI_PRECISION>>(m_data);
	m_shader->use().set_mat4("projectionMatrix", glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.f, -1.0f, 1.0f))
		.set_vec2("canvasPosition", canvasPosition)
		.set_vec2("canvasSize", canvasSize)
		.set_vec3("color", static_cast<hgui::kernel::Vector<HGUI_PRECISION, 3>>(m_color))
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
