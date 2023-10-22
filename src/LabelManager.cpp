#include <hgui/header/LabelManager.h>

#if defined(HGUI_DYNAMIC)
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
				uniform vec4 textColor;

				void main()
				{
					vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texturePosition).r);
					fragmentColor = vec4(textColor) * sampled;
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
#elif defined(HGUI_STATIC)
std::map<std::string, std::shared_ptr<hgui::kernel::Label>> hgui::LabelManager::m_labels;

const std::shared_ptr<hgui::kernel::Label>& hgui::LabelManager::create(const std::string& labelID, const std::string& text, const point& position, const std::shared_ptr<kernel::Font>& font, const std::tuple<unsigned int, color, float>& textOptions)
{
	if (m_labels.find(labelID) == m_labels.end())
	{
		m_labels[labelID] = std::make_shared<kernel::Label>(text,
			ShaderManager::get(HGUI_SHADER_LABEL), position, font, std::get<0>(textOptions),
			std::get<1>(textOptions), std::get<2>(textOptions));
		Widget::m_widgets[TagManager::get_current_tag()].push_back(m_labels[labelID]->weak_from_this());
		return m_labels[labelID];
	}
	else
	{
		throw std::runtime_error(("THERE IS ALREADY A LABEL WITH THE ID : " + labelID).c_str());
	}
}

const std::shared_ptr<hgui::kernel::Label>& hgui::LabelManager::get(const std::string& labelID)
{
	if (m_labels.find(labelID) != m_labels.end())
	{
		return m_labels[labelID];
	}
	else
	{
		throw std::runtime_error(("THERE IS NO LABEL WITH THE ID : " + labelID).c_str());
	}
}

void hgui::LabelManager::destroy(const std::initializer_list<std::string>& labelsID)
{
	if (labelsID.size())
	{
		for (const std::string& labelID : labelsID)
		{
			m_labels.erase(labelID);
		}
	}
	else
	{
		m_labels.clear();
	}
}
#endif