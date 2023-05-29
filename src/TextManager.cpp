#include <hgui/header/TextManager.h>

std::map<std::string, std::shared_ptr<hgui::kernel::TextArea>> hgui::TextManager::m_textAreas;

const std::shared_ptr<hgui::kernel::TextArea>& hgui::TextManager::create(const std::string& textAreaName, const std::string& text, glm::vec2 position, const std::shared_ptr<kernel::Font>& font, std::tuple<unsigned int, glm::vec3, float> textOptions)
{
	if (m_textAreas.find(textAreaName) == m_textAreas.end())
	{
		m_textAreas[textAreaName] = std::make_shared<kernel::TextArea>(text, ResourceManager::get_shader(HGUI_SHADER_TEXTAREA), position, font, std::get<0>(textOptions), std::get<1>(textOptions), std::get<2>(textOptions));
		WidgetManager::m_widgets[WidgetManager::m_currentTag].push_back(m_textAreas[textAreaName]);
		return m_textAreas[textAreaName];
	}
	else
	{
		throw std::exception(("THERE IS ALREADY A TEXT AREA WITH THE NAME : " + textAreaName).c_str());
	}
}

const std::shared_ptr<hgui::kernel::TextArea>& hgui::TextManager::get(const std::string& textAreaName)
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

void hgui::TextManager::delete_textArea(std::initializer_list<std::string> textAreasNames)
{
	if (textAreasNames.size())
	{
		for (const std::string& str : textAreasNames)
		{
			WidgetManager::delete_widget(m_textAreas[str]);
			m_textAreas.erase(str);
		}
	}
	else
	{
		m_textAreas.clear();
	}
}
