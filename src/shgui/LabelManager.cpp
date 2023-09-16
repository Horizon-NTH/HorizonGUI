#include <hgui/header/LabelManager.h>

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
