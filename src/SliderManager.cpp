#include <hgui/header/SliderManager.h>

#if defined(HGUI_DYNAMIC)
std::shared_ptr<hgui::kernel::Cursor> hgui::SliderManager::m_cursor(nullptr);

std::shared_ptr<hgui::kernel::Slider> hgui::SliderManager::create(const kernel::Ranges& range, const size& size, const point& position, const color& inactiveBarColor, const color& activeBarColor, const color& sliderColor, const Function& function, HGUI_PRECISION angularRotation)
{
	auto slider = std::make_shared<kernel::Slider>(range, inactiveBarColor, activeBarColor, size, position, sliderColor, function, angularRotation);
	std::weak_ptr<kernel::Slider> wwidget = std::static_pointer_cast<kernel::Slider>(slider->shared_from_this());
	Widget::m_widgets[TagManager::get_current_tag()].push_back(wwidget);
	slider->bind(inputs::OVER, []()
		{
			if (!m_cursor)
			{
				m_cursor = CursorManager::create(cursors::HAND);
			}
			m_cursor->use();
		});
	slider->bind(inputs::NOVER, []()
		{
			TaskManager::program(std::chrono::milliseconds(0), [&]()
				{
					if (auto isHover = []() -> bool
						{
							std::pair<double, double> mousePosition;
							glfwGetCursorPos(glfwGetCurrentContext(), &mousePosition.first, &mousePosition.second);
							const point click = {mousePosition.first, mousePosition.second};
							for (auto& tag : Widget::m_bindedTags)
							{
								for (auto& ptr : Widget::m_widgets[tag])
								{
									if (const auto slider_ptr = std::dynamic_pointer_cast<
										kernel::Slider>(ptr.lock()))
									{
										if (slider_ptr->is_inside(click))
										{
											return true;
										}
									}
								}
							}
							return false;
						}; !isHover())
					{
						m_cursor = nullptr;
					}
				});
		});
	slider->bind(std::make_tuple(inputs::OVER, buttons::LEFT, actions::PRESS), [wwidget]()
		{
			if (const auto widget = wwidget.lock())
			{
				std::pair<double, double> mousePosition;
				glfwGetCursorPos(glfwGetCurrentContext(), &mousePosition.first, &mousePosition.second);
				widget->set_slider_position(point(mousePosition.first, mousePosition.second));
				if (!widget->is_bind(std::make_pair(buttons::LEFT, actions::REPEAT)))
				{
					widget->bind(std::make_pair(buttons::LEFT, actions::REPEAT), [wwidget]
					{
						if (const auto widget = wwidget.lock())
						{
							std::pair<double, double> mousePosition;
							glfwGetCursorPos(glfwGetCurrentContext(), &mousePosition.first, &mousePosition.second);
							widget->set_slider_position(point(mousePosition.first, mousePosition.second));
						}
					});
				}
			}
		});
	slider->bind(std::make_pair(buttons::LEFT, actions::RELEASE), [wwidget]()
		{
			if (const auto widget = wwidget.lock())
			{
				if (widget->is_bind(std::make_pair(buttons::LEFT, actions::REPEAT)))
				{
					widget->unbind(std::make_pair(buttons::LEFT, actions::REPEAT));
				}
			}
		});
	return slider;
}
#elif defined(HGUI_STATIC)
std::map<std::string, std::shared_ptr<hgui::kernel::Slider>> hgui::SliderManager::m_sliders;

const std::shared_ptr<hgui::kernel::Slider>& hgui::SliderManager::create(const std::string& sliderID, const kernel::Ranges& range, const size& size, const point& position, const color& inactiveBarColor, const color& activeBarColor, const color& sliderColor, HGUI_PRECISION angularRotation)
{
	if (!m_sliders.contains(sliderID))
	{
		m_sliders[sliderID] = std::make_shared<kernel::Slider>(range, inactiveBarColor, activeBarColor, size, position, sliderColor, angularRotation);
		Widget::m_widgets[TagManager::get_current_tag()].push_back(m_sliders[sliderID]->weak_from_this());
		Widget::bind(m_sliders[sliderID], inputs::OVER, []()
		{
			if (!m_cursor)
			{
				m_cursor = CursorManager::create(cursors::HAND);
			}
			m_cursor->use();
		});
		Widget::bind(m_sliders[sliderID], inputs::NOVER, []()
			{
				hgui::TaskManager::program(std::chrono::milliseconds(0), [&]()
					{
						if (auto isHover = []() -> bool
							{
								std::pair<double, double> mousePosition;
								glfwGetCursorPos(glfwGetCurrentContext(), &mousePosition.first, &mousePosition.second);
								point click = {mousePosition.first, mousePosition.second};
								for (auto& tag : Widget::m_bindedTags)
								{
									for (auto& ptr : Widget::m_widgets[tag])
									{
										if (const auto slider = std::dynamic_pointer_cast<
											kernel::Slider>(ptr.lock()))
										{
											if (slider->is_inside(click))
											{
												return true;
											}
										}
									}
								}
								return false;
							}; !isHover())
						{
							CursorManager::get(HGUI_CURSOR_ARROW)->use();
						}
					});
			});
		Widget::bind(m_sliders[sliderID], std::make_tuple(inputs::OVER, buttons::LEFT, actions::PRESS), [&]()
			{
				if (auto widget = m_sliders[sliderID].lock())
				{
					std::pair<double, double> mousePosition;
					glfwGetCursorPos(glfwGetCurrentContext(), &mousePosition.first, &mousePosition.second);
					widget->set_slider_position(point(mousePosition.first, mousePosition.second));
					if (!widget->is_bind(std::make_pair(buttons::LEFT, actions::REPEAT)))
					{
						widget->bind(std::make_pair(buttons::LEFT, actions::REPEAT), [&]
						{
							if (auto widget = m_sliders[sliderID].lock())
							{
								std::pair<double, double> mousePosition;
								glfwGetCursorPos(glfwGetCurrentContext(), &mousePosition.first, &mousePosition.second);
								widget->set_slider_position(point(mousePosition.first, mousePosition.second));
							}
						});
					}
				}
			});
		Widget::bind(m_sliders[sliderID], std::make_pair(buttons::LEFT, actions::RELEASE), [&]()
			{
				if (auto widget = m_sliders[sliderID].lock())
				{
					if (widget->is_bind(std::make_pair(buttons::LEFT, actions::REPEAT)))
					{
						widget->unbind(std::make_pair(buttons::LEFT, actions::REPEAT));
					}
				}
			});
		return m_sliders[sliderID];
	}
	else
	{
		throw std::runtime_error(("THERE IS ALREADY A SLIDER WITH THE ID : " + sliderID).c_str());
	}
}

const std::shared_ptr<hgui::kernel::Slider>& hgui::SliderManager::get(const std::string& sliderID)
{
	if (m_sliders.contains(sliderID))
	{
		return m_sliders[sliderID];
	}
	else
	{
		throw std::runtime_error(("THERE IS NO SLIDERS WITH THE ID : " + sliderID).c_str());
	}
}

void hgui::SliderManager::destroy(const std::initializer_list<std::string>& slidersID)
{
	if (slidersID.size())
	{
		for (const std::string& id : slidersID)
		{
			m_sliders.erase(id);
		}
	}
	else
	{
		m_sliders.clear();
	}
}
#endif