#include <hgui/header/MouseManager.h>

std::map<std::variant<hgui::input::MouseInput, std::pair<hgui::input::MouseButton, hgui::input::Action>, std::tuple<hgui::input::MouseInput, hgui::input::MouseButton, hgui::input::Action>>, std::pair<std::shared_ptr<hgui::Timer>, std::function<void()>>> hgui::MouseManager::m_inputs;

void hgui::MouseManager::bind(std::variant<hgui::input::MouseInput, std::pair<hgui::input::MouseButton, hgui::input::Action>, std::tuple<input::MouseInput, input::MouseButton, input::Action>> action, std::function<void()> function)
{
	if (m_inputs.find(action) == m_inputs.end())
	{
		m_inputs[action] = { std::make_shared<Timer>(), function };
	}
	else
	{
		throw std::exception("THERE IS ALREADY A FUNCTION ASSOCIATED TO THIS INPUT");
	}
}

void hgui::MouseManager::unbind(std::variant<hgui::input::MouseInput, std::pair<hgui::input::MouseButton, hgui::input::Action>, std::tuple<input::MouseInput, input::MouseButton, input::Action>> action)
{
	if (m_inputs.find(action) != m_inputs.end())
	{
		m_inputs.erase(action);
	}
	else
	{
		throw std::exception("THERE IS NO FUNCTION ASSOCIATED TO THIS INPUT");
	}
}

glm::vec2 hgui::MouseManager::get_position()
{
	std::pair<double, double> mousePosition;
	glfwGetCursorPos(WindowManager::get_current_windowPTR(), &mousePosition.first, &mousePosition.second);
	return glm::vec2(static_cast<float>(mousePosition.first), static_cast<float>(mousePosition.second));
}

void hgui::MouseManager::process()
{
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
			auto action = std::get<input::MouseInput>(input.first);
			std::pair<double, double> newMousePosition;
			glfwGetCursorPos(WindowManager::get_current_windowPTR(), &newMousePosition.first, &newMousePosition.second);
			kernel::Window* window = static_cast<kernel::Window*>(glfwGetWindowUserPointer(WindowManager::get_current_windowPTR()));
			switch (action)
			{
			case hgui::input::OVER:
				if (is_mouse_in_sector(newMousePosition, window->get_position(), window->get_size()))
				{
					input.second.second();
				}
				break;
			case hgui::input::NOVER:
				if (!is_mouse_in_sector(newMousePosition, window->get_position(), window->get_size()))
				{
					input.second.second();
				}
				break;
			case hgui::input::MOTION:
				if (is_mouse_in_sector(newMousePosition, window->get_position(), window->get_size())
					&& (lastMousePosition.first != newMousePosition.first || lastMousePosition.second != newMousePosition.second))
				{
					input.second.second();
				}
				break;
			case hgui::input::SCROLL:
				break;
			case hgui::input::SCROLL_UP:
				break;
			case hgui::input::SCROLL_DOWN:
				break;
			default:
				break;
			}
			lastMousePosition = newMousePosition;
		}
		else if (input.first.index() == 1)
		{
			if (is_action_verified({ std::get<std::pair<input::MouseButton, input::Action>>(input.first), input.second }))
			{
				input.second.second();
			}
		}
		else if (input.first.index() == 2)
		{
			auto action = std::get<std::tuple<input::MouseInput, input::MouseButton, input::Action>>(input.first);
			std::pair<double, double> newMousePosition;
			glfwGetCursorPos(WindowManager::get_current_windowPTR(), &newMousePosition.first, &newMousePosition.second);
			kernel::Window* window = static_cast<kernel::Window*>(glfwGetWindowUserPointer(WindowManager::get_current_windowPTR()));
			switch (std::get<0>(action))
			{
			case hgui::input::OVER:
				if (is_mouse_in_sector(newMousePosition, window->get_position(), window->get_size()))
				{
					if (is_action_verified({ {std::get<1>(action), std::get<2>(action)}, input.second }))
					{
						input.second.second();
					}
				}
				break;
			case hgui::input::NOVER:
				if (!is_mouse_in_sector(newMousePosition, window->get_position(), window->get_size()))
				{
					if (is_action_verified({ {std::get<1>(action), std::get<2>(action)}, input.second }))
					{
						input.second.second();
					}
				}
				break;
			case hgui::input::MOTION:
				if (is_mouse_in_sector(newMousePosition, window->get_position(), window->get_size())
					&& (lastMousePosition.first != newMousePosition.first || lastMousePosition.second != newMousePosition.second))
				{
					if (is_action_verified({ {std::get<1>(action), std::get<2>(action)}, input.second }))
					{
						input.second.second();
					}
				}
				break;
			case hgui::input::SCROLL:
				break;
			case hgui::input::SCROLL_UP:
				break;
			case hgui::input::SCROLL_DOWN:
				break;
			default:
				break;
			}
			lastMousePosition = newMousePosition;
		}
	}
	//PROCESSING INPUT FOR WIDGET
	for (const std::string& tag : WidgetManager::m_bindedTags)
	{
		for (auto& widget : WidgetManager::get_widgets(tag))
		{
			if (WidgetManager::m_binds.find(widget) != WidgetManager::m_binds.end())
			{
				for (auto& input : WidgetManager::m_binds[widget])
				{
					static std::pair<double, double> lastMousePosition;
					if (!input.second.second)
					{
						continue;
					}
					if (input.first.index() == 0)
					{
						auto action = std::get<input::MouseInput>(input.first);
						std::pair<double, double> newMousePosition;
						glfwGetCursorPos(WindowManager::get_current_windowPTR(), &newMousePosition.first, &newMousePosition.second);
						kernel::Window* window = static_cast<kernel::Window*>(glfwGetWindowUserPointer(WindowManager::get_current_windowPTR()));
						switch (action)
						{
						case hgui::input::OVER:
							if (is_mouse_in_sector(newMousePosition, widget->get_position(), widget->get_size()))
							{
								input.second.second();
							}
							break;
						case hgui::input::NOVER:
							if (!is_mouse_in_sector(newMousePosition, widget->get_position(), widget->get_size()))
							{
								input.second.second();
							}
							break;
						case hgui::input::MOTION:
							if (is_mouse_in_sector(newMousePosition, widget->get_position(), widget->get_size())
								&& (lastMousePosition.first != newMousePosition.first || lastMousePosition.second != newMousePosition.second))
							{
								input.second.second();
							}
							break;
						case hgui::input::SCROLL:
							break;
						case hgui::input::SCROLL_UP:
							break;
						case hgui::input::SCROLL_DOWN:
							break;
						default:
							break;
						}
						lastMousePosition = newMousePosition;
					}
					else if (input.first.index() == 1)
					{
						if (is_action_verified({ std::get<std::pair<input::MouseButton, input::Action>>(input.first), input.second }))
						{
							input.second.second();
						}
					}
					else if (input.first.index() == 2)
					{
						auto action = std::get<std::tuple<input::MouseInput, input::MouseButton, input::Action>>(input.first);
						std::pair<double, double> newMousePosition;
						glfwGetCursorPos(WindowManager::get_current_windowPTR(), &newMousePosition.first, &newMousePosition.second);
						switch (std::get<0>(action))
						{
						case hgui::input::OVER:
							if (is_mouse_in_sector(newMousePosition, widget->get_position(), widget->get_size()))
							{
								if (is_action_verified({ {std::get<1>(action), std::get<2>(action)}, input.second }))
								{
									input.second.second();
								}
							}
							else
							{
								input.second.first->reset();
							}
							break;
						case hgui::input::NOVER:
							if (!is_mouse_in_sector(newMousePosition, widget->get_position(), widget->get_size()))
							{
								if (is_action_verified({ {std::get<1>(action), std::get<2>(action)}, input.second }))
								{
									input.second.second();
								}
							}
							else
							{
								input.second.first->reset();
							}
							break;
						case hgui::input::MOTION:
							if (is_mouse_in_sector(newMousePosition, widget->get_position(), widget->get_size()))
							{
								if ((lastMousePosition.first != newMousePosition.first || lastMousePosition.second != newMousePosition.second) &&
									is_action_verified({ {std::get<1>(action), std::get<2>(action)}, input.second }))
								{
									input.second.second();
								}
							}
							else
							{
								input.second.first->reset();
							}
							break;
						case hgui::input::SCROLL:
							break;
						case hgui::input::SCROLL_UP:
							break;
						case hgui::input::SCROLL_DOWN:
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
}

void hgui::MouseManager::scroll(GLFWwindow* window, double xOffset, double yOffset)
{
	/*
	if (yOffset < 0.0)
	{
		for (const auto& input : m_inputs)
		{
			if (!input.first.index() && std::get<input::MouseInput>(input.first) == input::SCROLL_DOWN)
			{
				if (input.second.second)
				{
					input.second.second();
				}
			}
		}
	}
	else if (yOffset > 0.0)
	{
		for (const auto& input : m_inputs)
		{
			if (!input.first.index() && std::get<input::MouseInput>(input.first) == input::SCROLL_UP)
			{
				if (input.second.second)
				{
					input.second.second();
				}
			}
		}
	}
	for (const auto& input : m_inputs)
	{
		if (!input.first.index() && std::get<input::MouseInput>(input.first) == input::SCROLL)
		{
			if (input.second.second)
			{
				input.second.second();
			}
		}
	}
	*/
}

bool hgui::MouseManager::is_mouse_in_sector(std::pair<double, double> mousePosition, glm::vec2 sectorPosition, glm::vec2 sectorSize)
{
	return mousePosition.first >= sectorPosition.x && mousePosition.second >= sectorPosition.y && mousePosition.first <= sectorPosition.x + sectorSize.x && mousePosition.second <= sectorPosition.y + sectorSize.y;
}

bool hgui::MouseManager::is_action_verified(const std::pair<std::pair<input::MouseButton, input::Action>, std::pair<std::shared_ptr<Timer>, std::function<void()>>>& input)
{
	auto action = glfwGetMouseButton(WindowManager::get_current_windowPTR(), input.first.first);
	switch (action)
	{
	case input::PRESS:
		if (!input.second.first->counting())
		{
			input.second.first->start();
			if (action == input.first.second)
			{
				return true;
			}
		}
		break;
	case input::RELEASE:
		if (input.second.first->counting())
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
	if (input.first.second == input::REPEAT && input.second.first->get_time() >= 0.2)
	{
		return true;
	}
	return false;
}
