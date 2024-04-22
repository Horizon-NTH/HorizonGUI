#include "../include/hgui/header/SliderManager.h"
#include "../include/hgui/header/TagManager.h"
#include "../include/hgui/header/TaskManager.h"
#include "../include/hgui/header/CursorManager.h"

#if defined(HGUI_DYNAMIC)
std::shared_ptr<hgui::kernel::Slider> hgui::SliderManager::create(const kernel::Ranges& range, const size& size, const point& position, const color& inactiveBarColor, const color& activeBarColor, const color& sliderColor, const Function& function, HGUI_PRECISION rotation)
{
	auto slider = std::make_shared<kernel::Slider>(range, inactiveBarColor, activeBarColor, size, position, sliderColor, function, rotation);
	std::weak_ptr wwidget = std::static_pointer_cast<kernel::Slider>(slider->shared_from_this());
	auto cursor = CursorManager::create(cursors::HAND);
	auto dragged = std::make_shared<bool>(false);
	slider->bind(inputs::OVER, [cursor]
		{
			CursorManager::use(cursor);
		});
	slider->bind(inputs::NOVER, [cursor, dragged]
		{
			TaskManager::program(std::chrono::milliseconds(0), [cursor, dragged]
				{
					if (!*dragged && CursorManager::get_cursor_used() == cursor)
					{
						CursorManager::use(nullptr);
					}
				});
		});
	slider->bind(std::make_tuple(inputs::OVER, buttons::LEFT, actions::PRESS), [wwidget, dragged]
		{
			if (const auto widget = wwidget.lock())
			{
				std::pair<double, double> mousePosition;
				glfwGetCursorPos(glfwGetCurrentContext(), &mousePosition.first, &mousePosition.second);
				widget->set_slider_position(point(mousePosition.first, mousePosition.second));
				if (!widget->is_bind(std::make_pair(buttons::LEFT, actions::REPEAT)))
				{
					*dragged = true;
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
	slider->bind(std::make_pair(buttons::LEFT, actions::RELEASE), [wwidget, cursor, dragged]
		{
			if (const auto widget = wwidget.lock())
			{
				if (widget->is_bind(std::make_pair(buttons::LEFT, actions::REPEAT)))
				{
					widget->unbind(std::make_pair(buttons::LEFT, actions::REPEAT));
				}
				TaskManager::program(std::chrono::milliseconds(0), [cursor, dragged, widget]
					{
						*dragged = false;
						if (CursorManager::get_cursor_used() == cursor)
						{
							std::pair<double, double> mousePosition;
							glfwGetCursorPos(glfwGetCurrentContext(), &mousePosition.first, &mousePosition.second);
							if (widget && !widget->is_inside(point(mousePosition.first, mousePosition.second)))
								CursorManager::use(nullptr);
						}
					});
			}
		});
	return slider;
}
#elif defined(HGUI_STATIC)
#include "../include/hgui/header/Cursor.h"
std::map<std::string, std::shared_ptr<hgui::kernel::Slider>> hgui::SliderManager::m_sliders;

const std::shared_ptr<hgui::kernel::Slider>& hgui::SliderManager::create(const std::string& sliderID, const kernel::Ranges& range, const size& size, const point& position, const color& inactiveBarColor, const color& activeBarColor, const color& sliderColor, const Function& function, HGUI_PRECISION angularRotation)
{
	if (!m_sliders.contains(sliderID))
	{
		m_sliders[sliderID] = std::make_shared<kernel::Slider>(range, inactiveBarColor, activeBarColor, size, position, sliderColor, function, angularRotation);
		kernel::Widget::bind(m_sliders[sliderID], inputs::OVER, []
			{
				CursorManager::use(CursorManager::get(HGUI_CURSOR_HAND));
			});
		kernel::Widget::bind(m_sliders[sliderID], inputs::NOVER, []
			{
				TaskManager::program(std::chrono::milliseconds(0), [&]
					{
						if (auto isHover = []() -> bool
							{
								std::pair<double, double> mousePosition;
								glfwGetCursorPos(glfwGetCurrentContext(), &mousePosition.first, &mousePosition.second);
								const point click = {mousePosition.first, mousePosition.second};
								for (auto& tag : kernel::Widget::get_active_tag())
								{
									for (auto& ptr : kernel::Widget::get_widgets(tag))
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
							CursorManager::use(CursorManager::get(HGUI_CURSOR_ARROW));
						}
					});
			});
		kernel::Widget::bind(m_sliders[sliderID], std::make_tuple(inputs::OVER, buttons::LEFT, actions::PRESS), [sliderID]
			{
				const auto widget = m_sliders[sliderID];
				std::pair<double, double> mousePosition;
				glfwGetCursorPos(glfwGetCurrentContext(), &mousePosition.first, &mousePosition.second);
				widget->set_slider_position(point(mousePosition.first, mousePosition.second));
				if (!widget->is_bind(std::make_pair(buttons::LEFT, actions::REPEAT)))
				{
					widget->bind(std::make_pair(buttons::LEFT, actions::REPEAT), [widget]
						{
							std::pair<double, double> mousePosition;
							glfwGetCursorPos(glfwGetCurrentContext(), &mousePosition.first, &mousePosition.second);
							widget->set_slider_position(point(mousePosition.first, mousePosition.second));
						});
				}
			});
		kernel::Widget::bind(m_sliders[sliderID], std::make_pair(buttons::LEFT, actions::RELEASE), [sliderID]
			{
				if (const auto widget = m_sliders[sliderID]; widget->is_bind(std::make_pair(buttons::LEFT, actions::REPEAT)))
				{
					widget->unbind(std::make_pair(buttons::LEFT, actions::REPEAT));
				}
			});
		return m_sliders[sliderID];
	}
	throw std::runtime_error(("THERE IS ALREADY A SLIDER WITH THE ID : " + sliderID).c_str());
}

const std::shared_ptr<hgui::kernel::Slider>& hgui::SliderManager::get(const std::string& sliderID)
{
	if (m_sliders.contains(sliderID))
	{
		return m_sliders[sliderID];
	}
	throw std::runtime_error(("THERE IS NO SLIDERS WITH THE ID : " + sliderID).c_str());
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
