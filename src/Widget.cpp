#include "../include/hgui/header/Widget.h"
#include "../include/hgui/header/TagManager.h"
#include "../include/hgui/header/TaskManager.h"
#include "../include/hgui/header/Timer.h"
#include "../include/hgui/header/VertexArrayObject.h"
#include "../include/hgui/header/VertexBufferObject.h"

hgui::kernel::Widget::Widget(const std::shared_ptr<Shader>& shader, size size, point position) :
	m_shader(shader),
	m_VAO(std::make_shared<VertexArrayObject>()),
	m_VBO(std::make_shared<VertexBufferObject>()),
	m_size(std::move(size)),
	m_position(std::move(position))
{
	auto tag = TagManager::get_current_tag();
	m_taskID = TaskManager::program(std::chrono::milliseconds{}, [&, tag]
		{
			m_widgets[tag].push_back(weak_from_this());
			m_taskID.clear();
		});
}

hgui::kernel::Widget::~Widget()
{
	if (!m_taskID.empty())
		TaskManager::deprogram(m_taskID);
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

const hgui::point& hgui::kernel::Widget::get_position() const
{
	return m_position;
}

const hgui::size& hgui::kernel::Widget::get_size() const
{
	return m_size;
}

void hgui::kernel::Widget::set_position(const point& newPosition)
{
	m_position = newPosition;
}

void hgui::kernel::Widget::set_size(const size& newSize)
{
	m_size = newSize;
}

void hgui::kernel::Widget::bind(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action, const std::function<void()>& function)
{
	bind(shared_from_this(), action, function);
}

bool hgui::kernel::Widget::is_bind(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action)
{
	return is_bind(shared_from_this(), action);
}

void hgui::kernel::Widget::unbind(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action)
{
	unbind(shared_from_this(), action);
}

void hgui::kernel::Widget::bind(const std::variant<std::shared_ptr<Widget>, std::string, std::vector<std::string>>& widgets, const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action, const std::function<void()>& function)
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

bool hgui::kernel::Widget::is_bind(const std::shared_ptr<Widget>& widget, const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action)
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

void hgui::kernel::Widget::unbind(const std::variant<std::shared_ptr<Widget>, std::string, std::vector<std::string>>& widgets, const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action)
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

void hgui::kernel::Widget::active(const std::vector<std::string>& tags)
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

const std::vector<std::string>& hgui::kernel::Widget::get_active_tag()
{
	return m_bindedTags;
}

const std::vector<std::weak_ptr<hgui::kernel::Widget>>& hgui::kernel::Widget::get_widgets(const std::string& tag)
{
	if (const std::vector<std::string>& tagsList = TagManager::get_tags(); std::ranges::find(tagsList, tag) != tagsList.end())
	{
		return m_widgets[tag];
	}
	throw std::runtime_error(("THERE IS NO TAG WITH THE NAME : " + tag).c_str());
}

void hgui::kernel::Widget::update()
{
	for (const auto& Widgets : m_widgets | std::views::values)
	{
		for (const auto& ptr : Widgets)
		{
			if (const auto widget = ptr.lock())
			{
				widget->m_position.update();
				widget->m_size.update();
				widget->set_size(widget->m_size);
				widget->set_position(widget->m_position);
			}
		}
	}
}
