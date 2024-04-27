#include "../include/hgui/header/MouseManager.h"
#include "../include/hgui/header/Widget.h"
#include "../include/hgui/header/Timer.h"
#include "../include/hgui/header/Window.h"

void hgui::MouseManager::bind(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action, const std::function<void()>& function)
{
	if (!is_bind(action))
	{
		m_inputs[action] = {std::make_shared<Timer>(), function};
	}
	else
	{
		throw std::runtime_error("THERE IS ALREADY A FUNCTION ASSOCIATED TO THIS INPUT");
	}
}

bool hgui::MouseManager::is_bind(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action)
{
	return m_inputs.contains(action);
}

void hgui::MouseManager::unbind(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action)
{
	if (is_bind(action))
	{
		m_inputs.erase(action);
	}
	else
	{
		throw std::runtime_error("THERE IS NO FUNCTION ASSOCIATED TO THIS INPUT");
	}
}

void hgui::MouseManager::bind_click_callback(const std::variant<std::function<void()>, std::function<void(buttons, actions)>>& function)
{
	m_clickCallback = function;
}

void hgui::MouseManager::bind_scroll_callback(const std::variant<std::function<void()>, std::function<void(double, double)>>& function)
{
	m_scrollCallback = function;
}

hgui::kernel::Point<HGUI_PRECISION> hgui::MouseManager::get_position()
{
	std::pair<double, double> mousePosition;
	glfwGetCursorPos(glfwGetCurrentContext(), &mousePosition.first, &mousePosition.second);
	return {mousePosition.first, mousePosition.second};
}

void hgui::MouseManager::process()
{
	std::vector<std::function<void()>> toDo;
	//PROCESSING INPUTS
	for (auto& input : m_inputs)
	{
		static point lastMousePosition;
		if (!input.second.second)
		{
			continue;
		}
		if (input.first.index() == 0)
		{
			auto& action = std::get<inputs>(input.first);
			point newMousePosition = get_position();
			const auto* window = static_cast<kernel::Window*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));
			switch (action)
			{
				case inputs::OVER:
					if (is_mouse_in_sector(newMousePosition, window->get_position(), window->get_size()))
					{
						toDo.push_back(input.second.second);
					}
					break;
				case inputs::NOVER:
					if (!is_mouse_in_sector(newMousePosition, window->get_position(), window->get_size()))
					{
						toDo.push_back(input.second.second);
					}
					break;
				case inputs::MOTION:
					if (is_mouse_in_sector(newMousePosition, window->get_position(), window->get_size())
					    && (lastMousePosition.x != newMousePosition.x || lastMousePosition.y != newMousePosition.y))
					{
						toDo.push_back(input.second.second);
					}
					break;
				default:
					break;
			}
			lastMousePosition = newMousePosition;
		}
		else if (input.first.index() == 1)
		{
			if (is_action_verified({std::get<std::pair<buttons, actions>>(input.first), input.second}))
			{
				toDo.push_back(input.second.second);
			}
		}
		else if (input.first.index() == 2)
		{
			auto& action = std::get<std::tuple<inputs, buttons, actions>>(input.first);
			point newMousePosition = get_position();
			const auto* window = static_cast<kernel::Window*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));
			switch (std::get<0>(action))
			{
				case inputs::OVER:
					if (is_mouse_in_sector(newMousePosition, window->get_position(), window->get_size()))
					{
						if (is_action_verified({{std::get<1>(action), std::get<2>(action)}, input.second}))
						{
							toDo.push_back(input.second.second);
						}
					}
					else
					{
						input.second.first->reset();
					}
					break;
				case inputs::NOVER:
					if (!is_mouse_in_sector(newMousePosition, window->get_position(), window->get_size()))
					{
						if (is_action_verified({{std::get<1>(action), std::get<2>(action)}, input.second}))
						{
							toDo.push_back(input.second.second);
						}
					}
					else
					{
						input.second.first->reset();
					}
					break;
				case inputs::MOTION:
					if (is_mouse_in_sector(newMousePosition, window->get_position(), window->get_size())
					    && (lastMousePosition.x != newMousePosition.x || lastMousePosition.y != newMousePosition.y))
					{
						if (is_action_verified({{std::get<1>(action), std::get<2>(action)}, input.second}))
						{
							toDo.push_back(input.second.second);
						}
					}
					else
					{
						input.second.first->reset();
					}
					break;
				default:
					break;
			}
			lastMousePosition = newMousePosition;
		}
	}
	//PROCESSING INPUT FOR WIDGET
	for (const std::string& tag : kernel::Widget::get_active_tag())
	{
		for (auto& wwidget : kernel::Widget::get_widgets(tag))
		{
			if (kernel::Widget::m_binds.contains(wwidget))
			{
				for (auto& input : kernel::Widget::m_binds[wwidget])
				{
					static point lastMousePosition;
					const auto widget = wwidget.lock();
					if (!input.second.second || !widget)
					{
						continue;
					}
					if (input.first.index() == 0)
					{
						const auto& action = std::get<inputs>(input.first);
						point newMousePosition = get_position();
						switch (action)
						{
							case inputs::OVER:
								if (widget->is_inside(newMousePosition))
								{
									toDo.push_back(input.second.second);
								}
								break;
							case inputs::NOVER:
								if (!widget->is_inside(newMousePosition))
								{
									toDo.push_back(input.second.second);
								}
								break;
							case inputs::MOTION:
								if (widget->is_inside(newMousePosition)
								    && (lastMousePosition.x != newMousePosition.x ||
								        lastMousePosition.y != newMousePosition.y))
								{
									toDo.push_back(input.second.second);
								}
								break;
							default:
								break;
						}
						lastMousePosition = newMousePosition;
					}
					else if (input.first.index() == 1)
					{
						if (is_action_verified({std::get<std::pair<buttons, actions>>(input.first), input.second}))
						{
							toDo.push_back(input.second.second);
						}
					}
					else if (input.first.index() == 2)
					{
						auto& action = std::get<std::tuple<inputs, buttons, actions>>(input.first);
						point newMousePosition = get_position();
						switch (std::get<0>(action))
						{
							case inputs::OVER:
								if (widget->is_inside(newMousePosition))
								{
									if (is_action_verified({{std::get<1>(action), std::get<2>(action)}, input.second}))
									{
										toDo.push_back(input.second.second);
									}
								}
								else
								{
									input.second.first->reset();
								}
								break;
							case inputs::NOVER:
								if (!widget->is_inside(newMousePosition))
								{
									if (is_action_verified({{std::get<1>(action), std::get<2>(action)}, input.second}))
									{
										toDo.push_back(input.second.second);
									}
								}
								else
								{
									input.second.first->reset();
								}
								break;
							case inputs::MOTION:
								if (widget->is_inside(newMousePosition))
								{
									if ((lastMousePosition.x != newMousePosition.x ||
									     lastMousePosition.y != newMousePosition.y) &&
									    is_action_verified({{std::get<1>(action), std::get<2>(action)}, input.second}))
									{
										toDo.push_back(input.second.second);
									}
								}
								else
								{
									input.second.first->reset();
								}
								break;
							default:
								break;
						}
						lastMousePosition = newMousePosition;
					}
				}
			}
		}
	}
	for (const auto& function : toDo)
	{
		function();
	}
}

void hgui::MouseManager::scroll([[maybe_unused]] GLFWwindow* window, const double xOffset, const double yOffset)
{
	if (const auto functionWithoutScrollInformation = std::get_if<std::function<void()>>(&m_scrollCallback); functionWithoutScrollInformation && *functionWithoutScrollInformation)
	{
		(*functionWithoutScrollInformation)();
	}
	else if (const auto functionWithScrollInformation = std::get_if<std::function<void(double, double)>>(&m_scrollCallback); functionWithScrollInformation && *functionWithScrollInformation)
	{
		(*functionWithScrollInformation)(xOffset, yOffset);
	}
	std::vector<std::function<void()>> toDo;
	//PROCESSING INPUTS
	for (auto& input : m_inputs)
	{
		if (!input.second.second)
		{
			continue;
		}
		if (const auto action = std::get_if<inputs>(&input.first))
		{
			point mousePosition = get_position();
			const auto* window_ptr = static_cast<kernel::Window*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));
			switch (*action)
			{
				case inputs::SCROLL:
					if (is_mouse_in_sector(mousePosition, window_ptr->get_position(), window_ptr->get_size()))
					{
						toDo.push_back(input.second.second);
					}
					break;
				case inputs::SCROLL_UP:
					if (is_mouse_in_sector(mousePosition, window_ptr->get_position(), window_ptr->get_size()) && yOffset > 0.)
					{
						toDo.push_back(input.second.second);
					}
					break;
				case inputs::SCROLL_DOWN:
					if (is_mouse_in_sector(mousePosition, window_ptr->get_position(), window_ptr->get_size()) && yOffset < 0.)
					{
						toDo.push_back(input.second.second);
					}
					break;
				default:
					break;
			}
		}
		else if (auto actionWithInput = std::get_if<std::tuple<inputs, buttons, actions>>(&input.first))
		{
			point mousePosition = get_position();
			const auto* window_ptr = static_cast<kernel::Window*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));
			switch (std::get<0>(*actionWithInput))
			{
				case inputs::SCROLL:
					if (is_mouse_in_sector(mousePosition, window_ptr->get_position(), window_ptr->get_size()))
					{
						if (is_action_verified({{std::get<1>(*actionWithInput), std::get<2>(*actionWithInput)}, input.second}))
						{
							toDo.push_back(input.second.second);
						}
					}
					else
					{
						input.second.first->reset();
					}
					break;
				case inputs::SCROLL_UP:
					if (is_mouse_in_sector(mousePosition, window_ptr->get_position(), window_ptr->get_size()) && yOffset > 0.)
					{
						if (is_action_verified({{std::get<1>(*actionWithInput), std::get<2>(*actionWithInput)}, input.second}))
						{
							toDo.push_back(input.second.second);
						}
					}
					else
					{
						input.second.first->reset();
					}
					break;
				case inputs::SCROLL_DOWN:
					if (is_mouse_in_sector(mousePosition, window_ptr->get_position(), window_ptr->get_size()) && yOffset < 0.)
					{
						if (is_action_verified({{std::get<1>(*actionWithInput), std::get<2>(*actionWithInput)}, input.second}))
						{
							toDo.push_back(input.second.second);
						}
					}
					else
					{
						input.second.first->reset();
					}
					break;
				default:
					break;
			}
		}
	}
	//PROCESSING INPUT FOR WIDGET
	for (const std::string& tag : kernel::Widget::get_active_tag())
	{
		for (auto& wwidget : kernel::Widget::get_widgets(tag))
		{
			if (kernel::Widget::m_binds.contains(wwidget))
			{
				for (auto& input : kernel::Widget::m_binds[wwidget])
				{
					const auto widget = wwidget.lock();
					if (!input.second.second || !widget)
					{
						continue;
					}
					if (const auto action = std::get_if<inputs>(&input.first))
					{
						point mousePosition = get_position();
						switch (*action)
						{
							case inputs::SCROLL:
								if (is_mouse_in_sector(mousePosition, widget->get_position(), widget->get_size()))
								{
									toDo.push_back(input.second.second);
								}
								break;
							case inputs::SCROLL_UP:
								if (is_mouse_in_sector(mousePosition, widget->get_position(), widget->get_size()) && yOffset > 0.)
								{
									toDo.push_back(input.second.second);
								}
								break;
							case inputs::SCROLL_DOWN:
								if (is_mouse_in_sector(mousePosition, widget->get_position(), widget->get_size()) && yOffset < 0.)
								{
									toDo.push_back(input.second.second);
								}
								break;
							default:
								break;
						}
					}
					else if (auto actionWithInput = std::get_if<std::tuple<inputs, buttons, actions>>(&input.first))
					{
						point mousePosition = get_position();
						switch (std::get<0>(*actionWithInput))
						{
							case inputs::SCROLL:
								if (is_mouse_in_sector(mousePosition, widget->get_position(), widget->get_size()))
								{
									if (is_action_verified({{std::get<1>(*actionWithInput), std::get<2>(*actionWithInput)}, input.second}))
									{
										toDo.push_back(input.second.second);
									}
								}
								else
								{
									input.second.first->reset();
								}
								break;
							case inputs::SCROLL_UP:
								if (is_mouse_in_sector(mousePosition, widget->get_position(), widget->get_size()) && yOffset > 0.)
								{
									if (is_action_verified({{std::get<1>(*actionWithInput), std::get<2>(*actionWithInput)}, input.second}))
									{
										toDo.push_back(input.second.second);
									}
								}
								else
								{
									input.second.first->reset();
								}
								break;
							case inputs::SCROLL_DOWN:
								if (is_mouse_in_sector(mousePosition, widget->get_position(), widget->get_size()) && yOffset < 0.)
								{
									if (is_action_verified({{std::get<1>(*actionWithInput), std::get<2>(*actionWithInput)}, input.second}))
									{
										toDo.push_back(input.second.second);
									}
								}
								else
								{
									input.second.first->reset();
								}
								break;
							default:
								break;
						}
					}
				}
			}
		}
	}
	for (const auto& function : toDo)
	{
		function();
	}
}

bool hgui::MouseManager::is_mouse_in_sector(const point& mousePosition, const point& sectorPosition, const size& sectorSize)
{
	return mousePosition.x >= sectorPosition.x && mousePosition.y >= sectorPosition.y &&
	       mousePosition.x <= sectorPosition.x + sectorSize.width && mousePosition.y <= sectorPosition.y + sectorSize.height;
}

bool hgui::MouseManager::is_action_verified(const std::pair<std::pair<buttons, actions>, std::pair<std::shared_ptr<Timer>, std::function<void()>>>& input)
{
	switch (const auto action = static_cast<actions>(
		glfwGetMouseButton(glfwGetCurrentContext(), static_cast<int>(input.first.first))))
	{
		case actions::PRESS:
			if (!input.second.first->is_counting())
			{
				input.second.first->start();
				if (action == input.first.second)
				{
					return true;
				}
			}
			break;
		case actions::RELEASE:
			if (input.second.first->is_counting())
			{
				input.second.first->reset();
				if (action == input.first.second)
				{
					return true;
				}
			}
			break;
		default:
			break;
	}
	if (input.first.second == actions::REPEAT && input.second.first->is_counting())
	{
		return true;
	}
	return false;
}

void hgui::MouseManager::input([[maybe_unused]] GLFWwindow* window, int button, int action, [[maybe_unused]] int mods)
{
	if (const auto functionWithoutInputInformation = std::get_if<std::function<void()>>(&m_clickCallback); functionWithoutInputInformation && *functionWithoutInputInformation)
	{
		(*functionWithoutInputInformation)();
	}
	else if (const auto functionWithInputInformation = std::get_if<std::function<void(buttons, actions)>>(&m_clickCallback); functionWithInputInformation && *functionWithInputInformation)
	{
		(*functionWithInputInformation)(static_cast<buttons>(button), static_cast<actions>(action));
	}
}

bool hgui::operator==(const MouseAction& lhs, const MouseAction& rhs)
{
	return lhs.first == rhs.first && lhs.second == rhs.second;
}

bool hgui::operator==(const MouseCombinationAction& lhs, const MouseCombinationAction& rhs)
{
	return std::get<0>(lhs) == std::get<0>(rhs) && std::get<1>(lhs) == std::get<1>(rhs) && std::get<2>(lhs) == std::get<2>(rhs);
}

bool hgui::operator==(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& lhs, const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& rhs)
{
	if (lhs.index() != rhs.index())
	{
		return false;
	}
	if (const auto inputL = std::get_if<inputs>(&lhs); const auto inputR = std::get_if<inputs>(&rhs))
	{
		return *inputL == *inputR;
	}
	if (const auto inputL = std::get_if<std::pair<buttons, actions>>(&lhs); const auto inputR = std::get_if<std::pair<buttons, actions>>(&rhs))
	{
		return inputL->first == inputR->first && inputL->second == inputR->second;
	}
	if (const auto inputL = std::get_if<std::tuple<inputs, buttons, actions>>(&lhs); const auto inputR = std::get_if<std::tuple<inputs, buttons, actions>>(&rhs))
	{
		return std::get<0>(*inputL) == std::get<0>(*inputR) &&
		       std::get<1>(*inputL) == std::get<1>(*inputR) &&
		       std::get<2>(*inputL) == std::get<2>(*inputR);
	}
	return false;
}
