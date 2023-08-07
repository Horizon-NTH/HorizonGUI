#include <hgui/header/LabelManager.h>

std::map<std::string, std::shared_ptr<hgui::kernel::Label>> hgui::LabelManager::m_textAreas;

const std::shared_ptr<hgui::kernel::Label>& hgui::LabelManager::create(const std::string& textAreaName, const std::string& text, const point& position, const std::shared_ptr<kernel::Font>& font, const std::tuple<unsigned int, color, float>& textOptions)
{
	if (m_textAreas.find(textAreaName) == m_textAreas.end())
	{
		m_textAreas[textAreaName] = std::make_shared<kernel::Label>(text, 
			ResourceManager::get_shader(HGUI_SHADER_TEXTAREA), position, font, std::get<0>(textOptions), 
			std::get<1>(textOptions), std::get<2>(textOptions));
		Widget::m_widgets[TagManager::get_current_tag()].push_back(m_textAreas[textAreaName]);
		return m_textAreas[textAreaName];
	}
	else
	{
		throw std::exception(("THERE IS ALREADY A TEXT AREA WITH THE NAME : " + textAreaName).c_str());
	}
}

const std::shared_ptr<hgui::kernel::Label>& hgui::LabelManager::get(const std::string& textAreaName)
{
	if (m_textAreas.find(textAreaName) != m_textAreas.end())
	{
		return m_textAreas[textAreaName];
	}
	else
	{
		throw std::exception(("THERE IS NO TEXT AREA WITH THE NAME : " + textAreaName).c_str());
	}
}

void hgui::LabelManager::delete_textArea(const std::initializer_list<std::string>& textAreasNames)
{
	if (textAreasNames.size())
	{
		for (const std::string& text : textAreasNames)
		{
			Widget::delete_widget(m_textAreas[text]);
			m_textAreas.erase(text);
		}
	}
	else
	{
		for (auto& text : m_textAreas)
		{
			Widget::delete_widget(text.second);
		}
		m_textAreas.clear();
	}
}
