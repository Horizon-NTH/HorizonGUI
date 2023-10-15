#include <hgui/header/ButtonManager.h>

std::shared_ptr<hgui::kernel::Shader> hgui::ButtonManager::m_shader(nullptr);
std::shared_ptr<hgui::kernel::Cursor> hgui::ButtonManager::m_cursor(nullptr);

std::shared_ptr<hgui::kernel::Button> hgui::ButtonManager::create(const std::function<void()>& function, const size& size, const point& position, const std::shared_ptr<kernel::Texture>& texture, const color& color, float borderRadius,const std::string& text, const std::shared_ptr<kernel::Font>& font, const hgui::color& textColor, float angularRotation)
{
	if (!m_shader)
	{
		m_shader = ShaderManager::create(
			R"(
				#version 330 core

				layout (location = 0) in vec4 vertex;
				out vec2 texturePosition;

				uniform mat4 modelMatrix;
				uniform mat4 projectionMatrix;

				void main()
				{
					gl_Position = projectionMatrix * modelMatrix * vec4(vertex.xy, 0.0, 1.0);
					texturePosition = vertex.zw;
				}
			)",
			R"(
				#version 330 core
				in vec2 texturePosition;
				out vec4 fragmentColor;

				uniform sampler2D button;
				uniform vec3 buttonColor;

				uniform int focused;
				uniform bool custom;


				void main()
				{
					if (!custom)
					{
						fragmentColor = vec4(buttonColor, 1.0);
					}
					else
					{
						fragmentColor = vec4(buttonColor, 1.0) * texture(button, texturePosition);
					}
					if (focused == 1)
					{
						if (fragmentColor.w < 1)
						{
							float luminance = 0.2126 * fragmentColor.r + 0.7152 * fragmentColor.g + 0.0722 * fragmentColor.b;
							if (luminance > 0.5)
								fragmentColor = vec4(vec3(1.0), 0.05);
							else  
								fragmentColor = vec4(vec3(0.0), 0.05);
						}
						else
						{
							if (all(greaterThan(fragmentColor.xyz, vec3(0.1))))
								fragmentColor.xyz *= 0.9;
							else
								fragmentColor.xyz += 0.1;
						}

					}
					else if (focused == 2)
					{
						if (fragmentColor.w < 1)
						{
							float luminance = 0.2126 * fragmentColor.r + 0.7152 * fragmentColor.g + 0.0722 * fragmentColor.b;
							if (luminance > 0.5)
								fragmentColor = vec4(vec3(1.0), 0.1);
							else  
								fragmentColor = vec4(vec3(0.0), 0.1);
						}
						else
						{
							if (all(greaterThan(fragmentColor.xyz, vec3(0.1))))
								fragmentColor.xyz *= 0.8;
							else
								fragmentColor.xyz += 0.2;
						}
					}
				}
			)"
		);
	}
	float cornerAngularRadius = std::min(std::min(size.width, size.height) * 0.5f, borderRadius);
	auto widget = std::make_shared<kernel::Button>(function,
		m_shader, size, position,
		font ? LabelManager::create(text, position, font, TextOption(12u, textColor, 1.0f)) : nullptr,
		color, angularRotation, cornerAngularRadius, texture);
	auto& widgets = Widget::m_widgets[TagManager::get_current_tag()];
	widgets.insert(widgets.size() ? widgets.end() - 1 : widgets.end(), widget->weak_from_this());
	std::weak_ptr<kernel::Button> wwidget = std::static_pointer_cast<kernel::Button>(widget->shared_from_this());
	widget->bind(inputs::OVER, [wwidget]()
		{
			wwidget.lock()->set_state(state::HOVER);
			if (!m_cursor)
			{
				m_cursor = CursorManager::create(cursors::HAND);
			}
			m_cursor->use();
		});
	widget->bind(inputs::NOVER, [wwidget]()
		{
			wwidget.lock()->set_state(state::NORMAL);
			m_cursor = nullptr;
		});
	widget->bind(std::make_tuple(inputs::OVER, buttons::LEFT, actions::REPEAT), [wwidget]()
		{
			wwidget.lock()->set_state(state::PRESS);
		});
	widget->bind(std::make_tuple(inputs::OVER, buttons::LEFT, actions::RELEASE), [wwidget]()
		{
			m_cursor = nullptr;
			wwidget.lock()->press();
		});
	return widget;
}
