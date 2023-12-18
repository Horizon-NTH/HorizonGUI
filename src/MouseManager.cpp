#include <hgui/header/MouseManager.h>

std::map<std::variant<hgui::inputs, std::pair<hgui::buttons, hgui::actions>, std::tuple<hgui::inputs, hgui::buttons, hgui::actions>>, std::pair<std::shared_ptr<hgui::Timer>, std::function<void()>>> hgui::MouseManager::m_inputs;
std::variant<std::function<void()>, std::function<void(hgui::buttons, hgui::actions)>> hgui::MouseManager::m_clickCallback{};
std::variant<std::function<void()>, std::function<void(double, double)>> hgui::MouseManager::m_scrollCallback{};

void hgui::MouseManager::bind(const std::variant<inputs, std::pair<buttons, hgui::actions>, std::tuple<inputs, buttons, actions>>& action, const std::function<void()>& function)
{
	if (!is_bind(action))
	{
		m_inputs[action] = { std::make_shared<Timer>(), function };
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

void hgui::MouseManager::unbind(const std::variant<hgui::inputs, std::pair<buttons, hgui::actions>, std::tuple<hgui::inputs, buttons, actions>>& action)
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

hgui::dvec2 hgui::MouseManager::get_position()
{
	std::pair<double, double> mousePosition;
	glfwGetCursorPos(glfwGetCurrentContext(), &mousePosition.first, &mousePosition.second);
	return { mousePosition.first, mousePosition.second };
}

void hgui::MouseManager::process()
{
	std::vector<std::function<void()>> toDo;
	//PROCESSING INPUTS
	for (auto& input : m_inputs)
	{
		static std::pair<double, double> lastMousePosition;
		if (!input.second.second)
		{
			continue;
		}
		if (input.first.index() == 0)
		{
			auto& action = std::get<inputs>(input.first);
			std::pair<double, double> newMousePosition;
			glfwGetCursorPos(glfwGetCurrentContext(), &newMousePosition.first, &newMousePosition.second);
			auto* window = static_cast<kernel::Window*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));
			switch (action)
			{
			case hgui::inputs::OVER:
				if (is_mouse_in_sector(newMousePosition, window->get_position(), window->get_size()))
				{
					toDo.push_back(input.second.second);
				}
				break;
			case hgui::inputs::NOVER:
				if (!is_mouse_in_sector(newMousePosition, window->get_position(), window->get_size()))
				{
					toDo.push_back(input.second.second);
				}
				break;
			case hgui::inputs::MOTION:
				if (is_mouse_in_sector(newMousePosition, window->get_position(), window->get_size())
					&& (lastMousePosition.first != newMousePosition.first || lastMousePosition.second != newMousePosition.second))
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
			if (is_action_verified({ std::get<std::pair<buttons, actions>>(input.first), input.second }))
			{
				toDo.push_back(input.second.second);
			}
		}
		else if (input.first.index() == 2)
		{
			auto& action = std::get<std::tuple<inputs, buttons, actions>>(input.first);
			std::pair<double, double> newMousePosition;
			glfwGetCursorPos(glfwGetCurrentContext(), &newMousePosition.first, &newMousePosition.second);
			const auto* window = static_cast<kernel::Window*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));
			switch (std::get<0>(action))
			{
			case hgui::inputs::OVER:
				if (is_mouse_in_sector(newMousePosition, window->get_position(), window->get_size()))
				{
					if (is_action_verified({ {std::get<1>(action), std::get<2>(action)}, input.second }))
					{
						toDo.push_back(input.second.second);
					}
				}
				else
				{
					input.second.first->reset();
				}
				break;
			case hgui::inputs::NOVER:
				if (!is_mouse_in_sector(newMousePosition, window->get_position(), window->get_size()))
				{
					if (is_action_verified({ {std::get<1>(action), std::get<2>(action)}, input.second }))
					{
						toDo.push_back(input.second.second);
					}
				}
				else
				{
					input.second.first->reset();
				}
				break;
			case hgui::inputs::MOTION:
				if (is_mouse_in_sector(newMousePosition, window->get_position(), window->get_size())
					&& (lastMousePosition.first != newMousePosition.first || lastMousePosition.second != newMousePosition.second))
				{
					if (is_action_verified({ {std::get<1>(action), std::get<2>(action)}, input.second }))
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
	for (const std::string& tag : Widget::m_bindedTags)
	{
		for (auto& wwidget : Widget::get_widgets(tag))
		{
			if (Widget::m_binds.contains(wwidget))
			{
				for (auto& input : Widget::m_binds[wwidget])
				{
					const auto widget = wwidget.lock();
					static std::pair<double, double> lastMousePosition;
					if (!input.second.second || !widget)
					{
						continue;
					}
					if (input.first.index() == 0)
					{
						const auto& action = std::get<inputs>(input.first);
						std::pair<double, double> newMousePosition;
						glfwGetCursorPos(glfwGetCurrentContext(), &newMousePosition.first, &newMousePosition.second);
						switch (action)
						{
						case hgui::inputs::OVER:
							if (widget->is_inside(point(newMousePosition.first, newMousePosition.second)))
							{
								toDo.push_back(input.second.second);
							}
							break;
						case hgui::inputs::NOVER:
							if (!widget->is_inside(point(newMousePosition.first, newMousePosition.second)))
							{
								toDo.push_back(input.second.second);
							}
							break;
						case hgui::inputs::MOTION:
							if (widget->is_inside(point(newMousePosition.first, newMousePosition.second))
								&& (lastMousePosition.first != newMousePosition.first ||
									lastMousePosition.second != newMousePosition.second))
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
						if (is_action_verified({ std::get<std::pair<buttons, actions>>(input.first), input.second }))
						{
							toDo.push_back(input.second.second);
						}
					}
					else if (input.first.index() == 2)
					{
						auto& action = std::get<std::tuple<inputs, buttons, actions>>(input.first);
						std::pair<double, double> newMousePosition;
						glfwGetCursorPos(glfwGetCurrentContext(), &newMousePosition.first, &newMousePosition.second);
						switch (std::get<0>(action))
						{
						case hgui::inputs::OVER:
							if (widget->is_inside(point(newMousePosition.first, newMousePosition.second)))
							{
								if (is_action_verified({ {std::get<1>(action), std::get<2>(action)}, input.second }))
								{
									toDo.push_back(input.second.second);
								}
							}
							else
							{
								input.second.first->reset();
							}
							break;
						case hgui::inputs::NOVER:
							if (!widget->is_inside(point(newMousePosition.first, newMousePosition.second)))
							{
								if (is_action_verified({ {std::get<1>(action), std::get<2>(action)}, input.second }))
								{
									toDo.push_back(input.second.second);
								}
							}
							else
							{
								input.second.first->reset();
							}
							break;
						case hgui::inputs::MOTION:
							if (widget->is_inside(point(newMousePosition.first, newMousePosition.second)))
							{
								if ((lastMousePosition.first != newMousePosition.first ||
									lastMousePosition.second != newMousePosition.second) &&
									is_action_verified({ {std::get<1>(action), std::get<2>(action)}, input.second }))
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

void hgui::MouseManager::scroll(GLFWwindow* window, const double xOffset, const double yOffset)
{
	if (const auto function = std::get_if<std::function<void()>>(&m_scrollCallback))
	{
		if (*function)
		{
			(*function)();
		}
	}
	else if (const auto function = std::get_if<std::function<void(double, double)>>(&m_scrollCallback))
	{
		if (*function)
		{
			(*function)(xOffset, yOffset);
		}
	}
	std::vector<std::function<void()>> toDo;
	//PROCESSING INPUTS
	for (auto& input : m_inputs)
	{
		static std::pair<double, double> lastMousePosition;
		if (!input.second.second)
		{
			continue;
		}
		if (const auto action = std::get_if<inputs>(&input.first))
		{
			std::pair<double, double> newMousePosition;
			glfwGetCursorPos(glfwGetCurrentContext(), &newMousePosition.first, &newMousePosition.second);
			auto* window_ptr = static_cast<kernel::Window*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));
			switch (*action)
			{
			case hgui::inputs::SCROLL:
				if (is_mouse_in_sector(newMousePosition, window_ptr->get_position(), window_ptr->get_size()))
				{
					toDo.push_back(input.second.second);
				}
				break;
			case hgui::inputs::SCROLL_UP:
				if (is_mouse_in_sector(newMousePosition, window_ptr->get_position(), window_ptr->get_size()) && yOffset > 0.)
				{
					toDo.push_back(input.second.second);
				}
				break;
			case hgui::inputs::SCROLL_DOWN:
				if (is_mouse_in_sector(newMousePosition, window_ptr->get_position(), window_ptr->get_size()) && yOffset < 0.)
				{
					toDo.push_back(input.second.second);
				}
				break;
			default:
				break;
			}
			lastMousePosition = newMousePosition;
		}
		else if (auto action = std::get_if<std::tuple<inputs, buttons, actions>>(&input.first))
		{
			std::pair<double, double> newMousePosition;
			glfwGetCursorPos(glfwGetCurrentContext(), &newMousePosition.first, &newMousePosition.second);
			auto* window_ptr = static_cast<kernel::Window*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));
			switch (std::get<0>(*action))
			{
			case hgui::inputs::SCROLL:
				if (is_mouse_in_sector(newMousePosition, window_ptr->get_position(), window_ptr->get_size()))
				{
					if (is_action_verified({ {std::get<1>(*action), std::get<2>(*action)}, input.second }))
					{
						toDo.push_back(input.second.second);
					}
				}
				else
				{
					input.second.first->reset();
				}
				break;
			case hgui::inputs::SCROLL_UP:
				if (is_mouse_in_sector(newMousePosition, window_ptr->get_position(), window_ptr->get_size()) && yOffset > 0.)
				{
					if (is_action_verified({ {std::get<1>(*action), std::get<2>(*action)}, input.second }))
					{
						toDo.push_back(input.second.second);
					}
				}
				else
				{
					input.second.first->reset();
				}
				break;
			case hgui::inputs::SCROLL_DOWN:
				if (is_mouse_in_sector(newMousePosition, window_ptr->get_position(), window_ptr->get_size()) && yOffset < 0.)
				{
					if (is_action_verified({ {std::get<1>(*action), std::get<2>(*action)}, input.second }))
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
	for (const std::string& tag : Widget::m_bindedTags)
	{
		for (auto& wwidget : Widget::get_widgets(tag))
		{
			if (Widget::m_binds.contains(wwidget))
			{
				for (auto& input : Widget::m_binds[wwidget])
				{
					const auto widget = wwidget.lock();
					static std::pair<double, double> lastMousePosition;
					if (!input.second.second || !widget)
					{
						continue;
					}
					if (const auto action = std::get_if<inputs>(&input.first))
					{
						std::pair<double, double> newMousePosition;
						glfwGetCursorPos(glfwGetCurrentContext(), &newMousePosition.first, &newMousePosition.second);
						switch (*action)
						{
						case hgui::inputs::SCROLL:
							if (is_mouse_in_sector(newMousePosition, widget->get_position(), widget->get_size()))
							{
								toDo.push_back(input.second.second);
							}
							break;
						case hgui::inputs::SCROLL_UP:
							if (is_mouse_in_sector(newMousePosition, widget->get_position(), widget->get_size()) && yOffset > 0.)
							{
								toDo.push_back(input.second.second);
							}
							break;
						case hgui::inputs::SCROLL_DOWN:
							if (is_mouse_in_sector(newMousePosition, widget->get_position(), widget->get_size()) && yOffset < 0.)
							{
								toDo.push_back(input.second.second);
							}
							break;
						default:
							break;
						}
						lastMousePosition = newMousePosition;
					}
					else if (auto action = std::get_if<std::tuple<inputs, buttons, actions>>(&input.first))
					{
						std::pair<double, double> newMousePosition;
						glfwGetCursorPos(glfwGetCurrentContext(), &newMousePosition.first, &newMousePosition.second);
						switch (std::get<0>(*action))
						{
						case hgui::inputs::SCROLL:
							if (is_mouse_in_sector(newMousePosition, widget->get_position(), widget->get_size()))
							{
								if (is_action_verified({ {std::get<1>(*action), std::get<2>(*action)}, input.second }))
								{
									toDo.push_back(input.second.second);
								}
							}
							else
							{
								input.second.first->reset();
							}
							break;
						case hgui::inputs::SCROLL_UP:
							if (is_mouse_in_sector(newMousePosition, widget->get_position(), widget->get_size()) && yOffset > 0.)
							{
								if (is_action_verified({ {std::get<1>(*action), std::get<2>(*action)}, input.second }))
								{
									toDo.push_back(input.second.second);
								}
							}
							else
							{
								input.second.first->reset();
							}
							break;
						case hgui::inputs::SCROLL_DOWN:
							if (is_mouse_in_sector(newMousePosition, widget->get_position(), widget->get_size()) && yOffset < 0.)
							{
								if (is_action_verified({ {std::get<1>(*action), std::get<2>(*action)}, input.second }))
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

bool hgui::MouseManager::is_mouse_in_sector(const std::pair<double, double>& mousePosition, const point& sectorPosition, const size& sectorSize)
{
	return mousePosition.first >= sectorPosition.x && mousePosition.second >= sectorPosition.y &&
		mousePosition.first <= sectorPosition.x + sectorSize.width && mousePosition.second <= sectorPosition.y + sectorSize.height;
}

bool hgui::MouseManager::is_action_verified(const std::pair<std::pair<buttons, actions>, std::pair<std::shared_ptr<Timer>, std::function<void()>>>& input)
{
	switch (const auto action = static_cast<hgui::actions>(
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

void hgui::MouseManager::input(GLFWwindow* window, int button, int action, int mods)
{
	if (const auto function = std::get_if<std::function<void()>>(&m_clickCallback))
	{
		if (*function)
		{
			(*function)();
		}
	}
	else if (const auto function = std::get_if<std::function<void(buttons, actions)>>(&m_clickCallback))
	{
		if (*function)
		{
			(*function)(static_cast<buttons>(button), static_cast<actions>(action));
		}
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
	else if (auto inputL = std::get_if<inputs>(&lhs); auto inputR = std::get_if<inputs>(&rhs))
	{
		return *inputL == *inputR;
	}
	else if (auto inputL = std::get_if<std::pair<buttons, actions>>(&lhs); auto inputR = std::get_if<std::pair<buttons, actions>>(&rhs))
	{
		return inputL->first == inputR->first && inputL->second == inputR->second;
	}
	else if (auto inputL = std::get_if<std::tuple<inputs, buttons, actions>>(&lhs); auto inputR = std::get_if<std::tuple<inputs, buttons, actions>>(&rhs))
	{
		return std::get<0>(*inputL) == std::get<0>(*inputR) &&
			std::get<1>(*inputL) == std::get<1>(*inputR) &&
			std::get<2>(*inputL) == std::get<2>(*inputR);
	}
	return false;
}
