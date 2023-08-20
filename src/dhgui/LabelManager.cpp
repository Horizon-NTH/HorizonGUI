#include <hgui/header/LabelManager.h>

std::shared_ptr<hgui::kernel::Shader> hgui::LabelManager::m_shader(nullptr);

std::shared_ptr<hgui::kernel::Label> hgui::LabelManager::create(const std::string& text, const point& position, const std::shared_ptr<kernel::Font>& font, const std::tuple<unsigned int, color, float>& textOptions)
{
	if (!m_shader)
	{
		m_shader = ShaderManager::create(
			R"(
				#version 330 core

				layout (location = 0) in vec4 vertex;
				out vec2 texturePosition;

				uniform mat4 projectionMatrix;

				void main()
				{
					gl_Position = projectionMatrix * vec4(vertex.xy, 0.0, 1.0);
					texturePosition = vertex.zw;
				}
			)",
			R"(
				#version 330 core

				in vec2 texturePosition;
				out vec4 fragmentColor;

				uniform sampler2D text;
				uniform vec3 textColor;

				void main()
				{
					vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texturePosition).r);
					fragmentColor = vec4(textColor, 1.0) * sampled;
				}
			)"
		);
	}
	auto widget = std::make_shared<kernel::Label>(text,
		m_shader, position, font, std::get<0>(textOptions),
		std::get<1>(textOptions), std::get<2>(textOptions));
	Widget::m_widgets[TagManager::get_current_tag()].push_back(widget->weak_from_this());
	return widget;
}
