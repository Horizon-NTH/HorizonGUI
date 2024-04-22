#include "../include/hgui/header/TagManager.h"

std::string hgui::TagManager::create_tag(const std::string& newTag)
{
	if (std::ranges::find(m_tags, newTag) == m_tags.end())
	{
		m_tags.push_back(newTag);
		return newTag;
	}
	throw std::runtime_error(("THERE IS ALREADY A TAG WITH THE NAME : " + newTag).c_str());
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
	if (std::ranges::find(m_tags, tag) != m_tags.end())
	{
		m_currentTag = tag;
	}
	else
	{
		throw std::runtime_error(("THERE IS NO TAG WITH THE NAME : " + tag).c_str());
	}
}
