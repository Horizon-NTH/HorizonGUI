#include <hgui/header/Drawer.h>

hgui::kernel::Drawer::Drawer(const std::shared_ptr<hgui::kernel::Shader>& shader, const point& position, const size& size) : m_position(position),
m_size(size),
m_shaders(std::make_pair(nullptr, shader)),
m_shapes(std::make_shared<std::vector<std::shared_ptr<shape::Shape>>>())
{
	m_shaders.first = ShaderManager::create(
		R"(
				#version 330 core

				layout (location = 0) in vec2 vertex;
				layout (location = 1) in vec3 vertexColor;
				layout (location = 2) in float thicknessIN;

				out vec3 vcolor;
				out float thickness;

				uniform mat4 modelMatrix;
				uniform mat4 projectionMatrix;

				void main()
				{
					gl_Position = projectionMatrix * modelMatrix * vec4(vertex, 0.0, 1.0);
					vcolor = vertexColor;
					thickness = thicknessIN;
				}
			)",
		R"(
				#version 330 core

				in vec3 color;

				out vec4 fragmentColor;

				uniform vec2 canvasPosition;
				uniform vec2 canvasSize;

				void main()
				{
					fragmentColor = vec4(color, 1.0);
				}
			)",
		R"(
			#version 330 core
			layout (lines) in;
			layout (triangle_strip, max_vertices = 6) out;

			in float thickness[];
			in vec3 vcolor[];

			out vec3 color;

			void main()
			{
			    vec4 point1 = gl_in[0].gl_Position;
			    vec4 point2 = gl_in[1].gl_Position;

			    float m1 = (point1.y - point2.y) / (point1.x - point2.x);
			    float m2 = -1.0 / m1;

			    float cor_x = sqrt(pow(thickness[0] / 2.0, 2.0) / (pow(m2, 2.0) + 1.0));
			    float cor_y = sqrt(pow(thickness[0] / 2.0, 2.0) / (pow(m2, 2.0) + 1.0));

			    vec2 corner1, corner2, corner3, corner4;

			    if (m2 >= 0.0)
			    {
			        corner1 = vec2(point1.x + cor_x, point1.y + cor_y);
			        corner2 = vec2(point1.x - cor_x, point1.y - cor_y);
			        corner3 = vec2(point2.x + cor_x, point2.y + cor_y);
			        corner4 = vec2(point2.x - cor_x, point2.y - cor_y);
			    }
			    else
			    {
			        corner1 = vec2(point1.x - cor_x, point1.y + cor_y);
			        corner2 = vec2(point1.x + cor_x, point1.y - cor_y);
			        corner3 = vec2(point2.x - cor_x, point2.y + cor_y);
			        corner4 = vec2(point2.x + cor_x, point2.y - cor_y);
			    }
				color = vcolor[0];
			    gl_Position = vec4(corner1, 0.0, 1.0);
			    EmitVertex();
			    gl_Position = vec4(corner2, 0.0, 1.0);
			    EmitVertex();
			    gl_Position = vec4(corner3, 0.0, 1.0);
			    EmitVertex();
			    gl_Position = vec4(corner2, 0.0, 1.0);
			    EmitVertex();
			    gl_Position = vec4(corner3, 0.0, 1.0);
			    EmitVertex();
			    gl_Position = vec4(corner4, 0.0, 1.0);
			    EmitVertex();
			    EndPrimitive();
			}
		)"
	);
}

void hgui::kernel::Drawer::draw_rectangle(const point& topLeftVertex, const point& rightBottomVertex, const color& color, bool fill,
	float thickness) const
{
	m_shapes->push_back(std::make_shared<shape::Rectangle>(point(m_position + topLeftVertex), point(m_position + rightBottomVertex),
		color, fill, thickness));
}

void hgui::kernel::Drawer::draw_triangle(const point& firstVertex, const point& secondVertex, const point& thirdVertex, const color& color,
	bool fill, float thickness) const
{
	m_shapes->push_back(std::make_shared<shape::Triangle>(point(m_position + firstVertex), point(m_position + secondVertex),
		point(m_position + thirdVertex), color, fill, thickness));
}

void hgui::kernel::Drawer::draw_circle(const point& centerPosition, float radius, const color& color, bool fill, float thickness) const
{
	m_shapes->push_back(std::make_shared<shape::Circle>(point(m_position + centerPosition), radius, color, fill, thickness));
}

void hgui::kernel::Drawer::draw_line(const point& firstVertex, const point& secondVertex, const color& color, float thickness) const
{
	m_shapes->push_back(
		std::make_shared<shape::StraightLine>(point(m_position + firstVertex), point(m_position + secondVertex), color, thickness));
}

const std::shared_ptr<std::vector<std::shared_ptr<hgui::kernel::shape::Shape>>>& hgui::kernel::Drawer::get_shapes() const
{
	return m_shapes;
}

void hgui::kernel::Drawer::draw() const
{
	for (const auto& shape : *m_shapes)
	{
		shape->draw(m_shaders);
	}
}
