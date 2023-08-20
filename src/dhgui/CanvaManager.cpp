#include <hgui/header/CanvaManager.h>

std::shared_ptr<hgui::kernel::Shader> hgui::CanvaManager::m_shader(nullptr);

std::shared_ptr<hgui::kernel::Canva> hgui::CanvaManager::create(const std::shared_ptr<kernel::Shader>& shader, const size& size, const point& position, const color& color, float angularRotation)
{
	if (!m_shader)
	{
		m_shader = ShaderManager::create(
			R"(
				#version 330 core

				layout (location = 0) in vec2 vertex;
				layout (location = 1) in vec3 vertexColor;

				out vec3 color;

				uniform mat4 modelMatrix;
				uniform mat4 projectionMatrix;

				void main()
				{
					gl_Position = projectionMatrix * modelMatrix * vec4(vertex, 0.0, 1.0);
					color = vertexColor;
				}
			)",
			R"(
				#version 330 core

				in vec3 color;

				out vec4 fragmentColor;

				uniform vec2 canvaPosition;
				uniform vec2 canvaSize;

				void main()
				{
					fragmentColor = vec4(color, 1.0);
				}
			)"
		);
	}
	auto widget = std::make_shared<kernel::Canva>(shader ? shader :
		m_shader, size, position, color, angularRotation);
	Widget::m_widgets[TagManager::get_current_tag()].push_back(widget->weak_from_this());
	return widget;
}
