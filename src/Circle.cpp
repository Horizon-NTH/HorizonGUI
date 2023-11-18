#include <hgui/header/Circle.h>

std::shared_ptr<hgui::kernel::Shader> hgui::kernel::shape::Circle::m_shader(nullptr);

hgui::kernel::shape::Circle::Circle(const point& centerPosition, const float radius, const color& color, const bool fill,
                                    float thickness) : Shape(fill, thickness, color, std::make_pair(centerPosition, radius))
{
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
				uniform float thickness;
				uniform bool fill;

				void main()
				{
				    vec2 pixelCoords = gl_FragCoord.xy;

				    if (pixelCoords.x < canvasPosition.x || pixelCoords.x >= canvasPosition.x + canvasSize.x ||
				        pixelCoords.y < canvasPosition.y || pixelCoords.y >= canvasPosition.y + canvasSize.y ||
						(fill && distance(pixelCoords, center) > radius) || 
						(!fill && (distance(pixelCoords, center) > radius + thickness ||
						distance(pixelCoords, center) < radius - thickness)))
				    {
				        discard;
				    } 
					fragmentColor = vec4(color, 1.0);
				} 
			)"
		);
	}
}

void hgui::kernel::shape::Circle::draw(const hgui::point& canvasPosition, const hgui::size& canvasSize) const
{
	int width, height;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
	const auto [center, radius] = std::get<std::pair<hgui::point, HGUI_PRECISION>>(m_data);
	m_shader->use().set_mat4("projectionMatrix", glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.f, -1.0f, 1.0f))
		.set_vec2("canvasPosition", canvasPosition)
		.set_vec2("canvasSize", canvasSize)
		.set_vec2("center", center)
		.set_vec3("color", static_cast<hgui::kernel::Vector<HGUI_PRECISION, 3>>(m_color))
		.set_float("radius", radius)
		.set_float("thickness", m_thickness)
		.set_int("fill", m_fill);
	m_VAO->bind();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	m_VAO->unbind();
}
