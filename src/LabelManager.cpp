#include <hgui/header/LabelManager.h>
#include <hgui/header/GLSL.h>

#if defined(HGUI_DYNAMIC)
std::shared_ptr<hgui::kernel::Shader> hgui::LabelManager::m_shader(nullptr);

std::shared_ptr<hgui::kernel::Label> hgui::LabelManager::create(const std::string& text, const point& position, const std::shared_ptr<kernel::Font>& font, const std::tuple<unsigned int, color, HGUI_PRECISION>& textOptions, const HGUI_PRECISION angularRotation)
{
	if (!m_shader)
	{
		m_shader = ShaderManager::create(HGUI_GLSL_VERTEX_LABEL, HGUI_GLSL_FRAGMENT_LABEL);
	}
	auto widget = std::make_shared<kernel::Label>(text,
		m_shader, position, font, std::get<0>(textOptions),
		std::get<1>(textOptions), std::get<2>(textOptions), angularRotation);
	Widget::m_widgets[TagManager::get_current_tag()].push_back(widget->weak_from_this());
	return widget;
}
#elif defined(HGUI_STATIC)
std::map<std::string, std::shared_ptr<hgui::kernel::Label>> hgui::LabelManager::m_labels;

const std::shared_ptr<hgui::kernel::Label>& hgui::LabelManager::create(const std::string& labelID, const std::string& text, const point& position, const std::shared_ptr<kernel::Font>& font, const std::tuple<unsigned int, color, HGUI_PRECISION>& textOptions, HGUI_PRECISION angularRotation)
{
	if (!m_labels.contains(labelID))
	{
		m_labels[labelID] = std::make_shared<kernel::Label>(text,
			ShaderManager::get(HGUI_SHADER_LABEL), position, font, std::get<0>(textOptions),
			std::get<1>(textOptions), std::get<2>(textOptions), angularRotation);
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
	if (m_labels.contains(labelID))
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
		for (const std::string& id : labelsID)
		{
			m_labels.erase(id);
		}
	}
	else
	{
		m_labels.clear();
	}
}
#endif