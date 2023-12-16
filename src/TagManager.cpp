#include <hgui/header/TagManager.h>

std::string hgui::TagManager::m_currentTag;
std::vector<std::string> hgui::TagManager::m_tags;

std::string hgui::TagManager::create_tag(const std::string& newTag)
{
	if (std::find(m_tags.begin(), m_tags.end(), newTag) == m_tags.end())
	{
		m_tags.push_back(newTag);
		return newTag;
	}
	else
	{
		throw std::runtime_error(("THERE IS ALREADY A TAG WITH THE NAME : " + newTag).c_str());
	}
}

const std::vector<std::string>& hgui::TagManager::get_tags()
{
	return m_tags;
}

const std::string& hgui::TagManager::get_current_tag()
{
	return m_currentTag;
}

void hgui::TagManager::set_current_tag(const std::string& tag)
{
	if (std::find(m_tags.begin(), m_tags.end(), tag) != m_tags.end())
	{
		m_currentTag = tag;
	}
	else
	{
		throw std::runtime_error(("THERE IS NO TAG WITH THE NAME : " + tag).c_str());
	}
}