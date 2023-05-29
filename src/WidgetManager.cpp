#include <hgui/header/WidgetManager.h>

std::string hgui::WidgetManager::m_currentTag;
std::vector<std::string> hgui::WidgetManager::m_tags;
std::vector<std::string> hgui::WidgetManager::m_bindedTags;
std::map<std::shared_ptr<hgui::kernel::Widget>, std::vector<std::pair<std::variant<hgui::input::MouseInput, std::pair<hgui::input::MouseButton, hgui::input::Action>, std::tuple<hgui::input::MouseInput, hgui::input::MouseButton, hgui::input::Action>>, std::pair<std::shared_ptr<hgui::Timer>, std::function<void()>>>>> hgui::WidgetManager::m_binds;
std::map<std::string, std::vector<std::shared_ptr<hgui::kernel::Widget>>> hgui::WidgetManager::m_widgets;

std::string hgui::WidgetManager::create_tag(const std::string& newTag)
{
	if (std::find(m_tags.begin(), m_tags.end(), newTag) == m_tags.end())
	{
		m_tags.push_back(newTag);
		m_widgets[newTag];
		return newTag;
	}
	else
	{
		throw std::exception(("THERE IS ALREADY A TAG WITH THE NAME : " + newTag).c_str());
	}
}

const std::vector<std::string>& hgui::WidgetManager::get_tags()
{
	return m_tags;
}

const std::string& hgui::WidgetManager::get_current_tag()
{
	return m_currentTag;
}

void hgui::WidgetManager::set_current_tag(const std::string& tag)
{
	if (std::find(m_tags.begin(), m_tags.end(), tag) != m_tags.end())
	{
		m_currentTag = tag;
	}
	else
	{
		throw std::exception(("THERE IS NO TAG WITH THE NAME : " + tag).c_str());
	}
}

void hgui::WidgetManager::bind(std::variant<std::string, std::vector<std::string>, std::shared_ptr<kernel::Widget>> widgets, std::variant<input::MouseInput, std::pair<input::MouseButton, input::Action>, std::tuple<input::MouseInput, input::MouseButton, input::Action>> action, std::function<void()> function)
{
	if (widgets.index() == 0)
	{
		for (const auto& widget : get_widgets(std::get<std::string>(widgets)))
		{
			m_binds[widget].push_back({ action, {std::make_shared<Timer>(), function} });
		}
	}
	else if (widgets.index() == 1)
	{
		for (const std::string& tag : std::get<std::vector<std::string>>(widgets))
		{
			for (const auto& widget : get_widgets(tag))
			{
				m_binds[widget].push_back({ action, {std::make_shared<Timer>(), function} });
			}
		}
	}
	else if (widgets.index() == 2)
	{
		m_binds[std::get<std::shared_ptr<kernel::Widget>>(widgets)].push_back({action, {std::make_shared<Timer>(), function}});
	}
}

void hgui::WidgetManager::active(std::vector<std::string> tags)
{
	m_bindedTags.clear();
	for (const std::string& tag : tags.size() ? tags : m_tags)
	{
		if (std::find(m_tags.begin(), m_tags.end(), tag) != m_tags.end())
		{
			m_bindedTags.push_back(tag);
		}
	}
}

const std::vector<std::shared_ptr<hgui::kernel::Widget>>& hgui::WidgetManager::get_widgets(const std::string& tag)
{
	if (std::find(m_tags.begin(), m_tags.end(), tag) != m_tags.end())
	{
		return m_widgets[tag];
	}
	else
	{
		throw std::exception(("THERE IS NO TAG WITH THE NAME : " + tag).c_str());
	}
}

void hgui::WidgetManager::delete_widget(const std::shared_ptr<kernel::Widget>& widget)
{
	for (auto& vec : m_widgets)
	{
		auto it = std::find_if(vec.second.begin(), vec.second.end(), [widget](const auto& p) { return widget == p; });
		if (it != vec.second.end())
		{
			vec.second.erase(it);
		}
	}
}
