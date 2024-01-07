#include "../include/hgui/header/Widget.h"
#include "../include/hgui/header/TagManager.h"

std::vector<std::string> hgui::Widget::m_bindedTags;
std::map<std::weak_ptr<hgui::Widget>, std::vector<std::pair<std::variant<hgui::inputs, std::pair<hgui::buttons, hgui::actions>, std::tuple<hgui::inputs, hgui::buttons, hgui::actions>>, std::pair<std::shared_ptr<hgui::Timer>, std::function<void()>>>>, hgui::kernel::WeakPTRComparator<hgui::Widget>> hgui::Widget::m_binds;
std::map<std::string, std::vector<std::weak_ptr<hgui::Widget>>> hgui::Widget::m_widgets;

hgui::Widget::Widget(const std::shared_ptr<kernel::Shader>& shader, const size& size, const point& position, const color& color, const HGUI_PRECISION angularRotation) :
	m_shader(shader),
	m_VAO(std::make_shared<kernel::VertexArrayObject>()),
	m_VBO(std::make_shared<kernel::VertexBufferObject>()),
	m_size(size),
	m_position(position),
	m_color(color),
	m_angularRotation(angularRotation)
{
}

hgui::Widget::~Widget()
{
	for (auto& widgets : m_widgets | std::ranges::views::values)
	{
		std::erase_if(widgets, [](const std::weak_ptr<Widget>& widget) -> bool
			{
				return widget.expired();
			});
	}
	for (auto it = m_binds.begin(); it != m_binds.end();
	     it->first.expired() ? it = m_binds.erase(it) : it++);
}

const hgui::point& hgui::Widget::get_position() const
{
	return m_position;
}

const hgui::size& hgui::Widget::get_size() const
{
	return m_size;
}

HGUI_PRECISION hgui::Widget::get_rotation() const
{
	return m_angularRotation;
}

void hgui::Widget::set_position(const point& newPosition)
{
	m_position = newPosition;
}

void hgui::Widget::set_rotation(const HGUI_PRECISION newAngularRotation)
{
	m_angularRotation = newAngularRotation;
}

void hgui::Widget::bind(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action, const std::function<void()>& function)
{
	bind(shared_from_this(), action, function);
}

bool hgui::Widget::is_bind(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action)
{
	return is_bind(shared_from_this(), action);
}

void hgui::Widget::unbind(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action)
{
	unbind(shared_from_this(), action);
}

void hgui::Widget::bind(const std::variant<std::shared_ptr<Widget>, std::string, std::vector<std::string>>& widgets, const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action, const std::function<void()>& function)
{
	if (widgets.index() == 0)
	{
		const auto& widget = std::get<std::shared_ptr<Widget>>(widgets);
		if (is_bind(widget, action))
		{
			throw std::runtime_error("THERE IS ALREADY A BIND ASSOCIATED TO THIS WIDGET");
		}
		m_binds[widget].push_back({action, {std::make_shared<Timer>(), function}});
	}
	else if (widgets.index() == 1)
	{
		for (const auto& wwidget : get_widgets(std::get<std::string>(widgets)))
		{
			if (auto widget = wwidget.lock())
			{
				if (is_bind(widget, action))
				{
					throw std::runtime_error("THERE IS ALREADY A BIND ASSOCIATED TO THIS WIDGET");
				}
				m_binds[wwidget].push_back({action, {std::make_shared<Timer>(), function}});
			}
		}
	}
	else if (widgets.index() == 2)
	{
		for (const std::string& tag : std::get<std::vector<std::string>>(widgets))
		{
			for (const auto& wwidget : get_widgets(tag))
			{
				if (auto widget = wwidget.lock())
				{
					if (is_bind(widget, action))
					{
						throw std::runtime_error("THERE IS ALREADY A BIND ASSOCIATED TO THIS WIDGET");
					}
					m_binds[wwidget].push_back({action, {std::make_shared<Timer>(), function}});
				}
			}
		}
	}
}

bool hgui::Widget::is_bind(const std::shared_ptr<Widget>& widget, const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action)
{
	if (!m_binds.contains(widget))
	{
		return false;
	}
	using type = std::pair<std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>, std::pair<std::shared_ptr<Timer>, std::function<void()>>>;
	return std::ranges::any_of(m_binds[widget], [&](const type& el) -> bool
		{
			return el.first == action;
		});
}

void hgui::Widget::unbind(const std::variant<std::shared_ptr<Widget>, std::string, std::vector<std::string>>& widgets, const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action)
{
	using type = std::pair<std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>, std::pair<std::shared_ptr<Timer>, std::function<void()>>>;
	if (widgets.index() == 0)
	{
		const auto& widget = std::get<std::shared_ptr<Widget>>(widgets);
		if (!is_bind(widget, action))
		{
			throw std::runtime_error("THERE IS NO BIND ASSOCIATED TO THIS WIDGET");
		}
		std::erase_if(m_binds[widget], [&](const type& el) { return el.first == action; });
	}
	else if (widgets.index() == 1)
	{
		for (const auto& wwidget : get_widgets(std::get<std::string>(widgets)))
		{
			if (auto widget = wwidget.lock())
			{
				if (!is_bind(widget, action))
				{
					throw std::runtime_error("THERE IS NO BIND ASSOCIATED TO THIS WIDGET");
				}
				std::erase_if(m_binds[wwidget], [&](const type& el) { return el.first == action; });
			}
		}
	}
	else if (widgets.index() == 2)
	{
		for (const std::string& tag : std::get<std::vector<std::string>>(widgets))
		{
			for (const auto& wwidget : get_widgets(tag))
			{
				if (auto widget = wwidget.lock())
				{
					if (!is_bind(widget, action))
					{
						throw std::runtime_error("THERE IS NO BIND ASSOCIATED TO THIS WIDGET");
					}
					std::erase_if(m_binds[wwidget], [&](const type& el) { return el.first == action; });
				}
			}
		}
	}
}

void hgui::Widget::active(const std::vector<std::string>& tags)
{
	m_bindedTags.clear();
	for (const std::vector<std::string>& tagsList = TagManager::get_tags(); const std::string& tag : !tags.empty() ? tags : tagsList)
	{
		if (std::ranges::find(tagsList, tag) != tagsList.end())
		{
			m_bindedTags.push_back(tag);
		}
	}
	glfwSetCursor(glfwGetCurrentContext(), glfwCreateStandardCursor(GLFW_ARROW_CURSOR));
}

const std::vector<std::weak_ptr<hgui::Widget>>& hgui::Widget::get_widgets(const std::string& tag)
{
	if (const std::vector<std::string>& tagsList = TagManager::get_tags(); std::ranges::find(tagsList, tag) != tagsList.end())
	{
		return m_widgets[tag];
	}
	throw std::runtime_error(("THERE IS NO TAG WITH THE NAME : " + tag).c_str());
}
