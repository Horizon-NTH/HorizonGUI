#include "../include/hgui/header/SliderManager.h"
#include "../include/hgui/header/TagManager.h"
#include "../include/hgui/header/TaskManager.h"
#include "../include/hgui/header/CursorManager.h"

std::shared_ptr<hgui::kernel::Slider> hgui::SliderManager::create(const kernel::Ranges& range, const size& size, const point& position, const std::tuple<color, color, color>& colors, const Function& function)
{
	auto slider = std::make_shared<kernel::Slider>(range, size, position, colors, function);
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
