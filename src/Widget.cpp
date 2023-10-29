#include <hgui/header/Widget.h>

std::vector<std::string> hgui::Widget::m_bindedTags;
std::map<std::weak_ptr<hgui::Widget>, std::vector<std::pair<
	         std::variant<hgui::inputs, std::pair<hgui::buttons, hgui::actions>, std::tuple<hgui::inputs, hgui::buttons, hgui::actions>>,
	         std::pair<std::shared_ptr<hgui::Timer>, std::function<void()>>>>, hgui::kernel::WeakPTRComparator<hgui::Widget>>
hgui::Widget::m_binds;
std::map<std::string, std::vector<std::weak_ptr<hgui::Widget>>> hgui::Widget::m_widgets;

hgui::Widget::Widget(const std::shared_ptr<kernel::Shader>& shader, const size& size, const point& position,
                     const color& color) : m_shader(shader),
                                           m_VAO(std::make_shared<kernel::VertexArrayObject>()),
                                           m_VBO(std::make_shared<kernel::VertexBufferObject>()),
                                           m_size(size),
                                           m_position(position),
                                           m_color(color)
{
	if (!m_shader)
	{
		throw std::runtime_error("ERROR NEED SHADER TO CREATE A WIDGET");
	}
}

hgui::Widget::~Widget()
{
	for (auto& widgets : Widget::m_widgets)
	{
		std::erase_if(widgets.second, [](const std::weak_ptr<Widget>& widget) -> bool
			              {
				              return widget.expired();
			              });
	}
	for (auto it = Widget::m_binds.begin(); it != Widget::m_binds.end();
	     it->first.expired() ? it = Widget::m_binds.erase(it) : it++);
}

const hgui::point& hgui::Widget::get_position() const
{
	return m_position;
}

void hgui::Widget::set_position(const point& newPosition)
{
	m_position = newPosition;
}

const hgui::size& hgui::Widget::get_size() const
{
	return m_size;
}

void hgui::Widget::bind(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action,
                        const std::function<void()>& function)
{
	Widget::bind(shared_from_this(), action, function);
}

void hgui::Widget::unbind(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action)
{
	Widget::unbind(shared_from_this(), action);
}

void hgui::Widget::bind(const std::variant<std::shared_ptr<Widget>, std::string, std::vector<std::string>>& widgets,
                        const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action,
                        const std::function<void()>& function)
{
	if (widgets.index() == 0)
	{
		m_binds[std::get<std::shared_ptr<Widget>>(widgets)].push_back({action, {std::make_shared<Timer>(), function}});
	}
	else if (widgets.index() == 1)
	{
		for (const auto& widget : get_widgets(std::get<std::string>(widgets)))
		{
			m_binds[widget].push_back({action, {std::make_shared<Timer>(), function}});
		}
	}
	else if (widgets.index() == 2)
	{
		for (const std::string& tag : std::get<std::vector<std::string>>(widgets))
		{
			for (const auto& widget : get_widgets(tag))
			{
				m_binds[widget].push_back({action, {std::make_shared<Timer>(), function}});
			}
		}
	}
}

void hgui::Widget::unbind(const std::variant<std::shared_ptr<Widget>, std::string, std::vector<std::string>>& widgets,
                          const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action)
{
	auto toRemove = [&](const std::pair<std::variant<inputs, std::pair<buttons, actions>,
	                                                 std::tuple<inputs, buttons, actions>>, std::pair<
		                                    std::shared_ptr<Timer>, std::function<void()>>>& bind)
		{
			if (std::holds_alternative<inputs>(action) && std::holds_alternative<inputs>(bind.first))
			{
				return std::get<0>(action) == std::get<0>(bind.first);
			}
			else if (std::holds_alternative<std::pair<buttons, actions>>(action) &&
				std::holds_alternative<std::pair<buttons, actions>>(bind.first))
			{
				return std::get<1>(action) == std::get<1>(bind.first);
			}
			else if (std::holds_alternative<std::tuple<inputs, buttons, actions>>(action) &&
				std::holds_alternative<std::tuple<inputs, buttons, actions>>(bind.first))
			{
				return std::get<2>(action) == std::get<2>(bind.first);
			}
			return false;
		};
	if (widgets.index() == 0)
	{
		m_binds[std::get<std::shared_ptr<Widget>>(widgets)].erase(
			std::ranges::remove_if(m_binds[std::get<std::shared_ptr<Widget>>(widgets)], toRemove).begin(),
			m_binds[std::get<std::shared_ptr<Widget>>(widgets)].end());
	}
	else if (widgets.index() == 1)
	{
		for (const auto& widget : get_widgets(std::get<std::string>(widgets)))
		{
			std::erase_if(m_binds[widget], toRemove);
		}
	}
	else if (widgets.index() == 2)
	{
		for (const std::string& tag : std::get<std::vector<std::string>>(widgets))
		{
			for (const auto& widget : get_widgets(tag))
			{
				std::erase_if(m_binds[widget], toRemove);
			}
		}
	}
}

void hgui::Widget::active(const std::vector<std::string>& tags)
{
	m_bindedTags.clear();
	const std::vector<std::string>& tagsList = hgui::TagManager::get_tags();
	for (const std::string& tag : !tags.empty() ? tags : tagsList)
	{
		if (std::ranges::find(tagsList, tag) != tagsList.end())
		{
			m_bindedTags.push_back(tag);
		}
	}
}

const std::vector<std::weak_ptr<hgui::Widget>>& hgui::Widget::get_widgets(const std::string& tag)
{
	const std::vector<std::string>& tagsList = hgui::TagManager::get_tags();
	if (std::ranges::find(tagsList, tag) != tagsList.end())
	{
		return Widget::m_widgets[tag];
	}
	else
	{
		throw std::runtime_error(("THERE IS NO TAG WITH THE NAME : " + tag).c_str());
	}
}
