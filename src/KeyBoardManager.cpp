#include "../include/hgui/header/KeyBoardManager.h"
#include "../include/hgui/header/Timer.h"
#include "../include/hgui/header/TextInput.h"

bool hgui::kernel::VariantKeyComparator::operator()(const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& leftSide, const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& rightSide) const
{
	if (leftSide.index() == rightSide.index())
	{
		if (!leftSide.index())
		{
			const auto [leftKey, leftAction] = std::get<std::pair<keys, actions>>(leftSide);
			const auto [rightKey, rightAction] = std::get<std::pair<keys, actions>>(rightSide);
			if (leftKey == rightKey)
			{
				return leftAction < rightAction;
			}
			return leftKey < rightKey;
		}
		auto [leftKey, leftAction] = std::get<std::pair<std::vector<keys>, actions>>(leftSide);
		auto [rightKey, rightAction] = std::get<std::pair<std::vector<keys>, actions>>(rightSide);
		const int leftSum = std::accumulate(leftKey.begin(), leftKey.end(), 0, [](const int& sum, const keys& value)
			{
				return sum + static_cast<int>(value);
			});
		const int rightSum = std::accumulate(rightKey.begin(), rightKey.end(), 0, [](const int& sum, const keys& value)
			{
				return sum + static_cast<int>(value);
			});
		if (leftSum == rightSum)
		{
			return leftAction < rightAction;
		}
		return leftSum < rightSum;
	}
	return leftSide.index() < rightSide.index();
}

void hgui::KeyBoardManager::bind(const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& action, const std::function<void()>& function)
{
	if (!is_bind(action))
	{
		m_keys[action] = std::make_pair(std::make_shared<Timer>(), function);
	}
	else
	{
		throw std::runtime_error("THERE IS ALREADY A FUNCTION WITH THIS ASSOCIATION OF KEY AND ACTION");
	}
}

bool hgui::KeyBoardManager::is_bind(const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& action)
{
	return m_keys.contains(action);
}

const std::function<void()>& hgui::KeyBoardManager::get_bind(const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& action)
{
	if (is_bind(action))
	{
		return m_keys[action].second;
	}
	throw std::runtime_error("THERE IS NO FUNCTION WITH THIS ASSOCIATION OF KEY AND ACTION");
}

void hgui::KeyBoardManager::unbind(const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& action)
{
	if (is_bind(action))
	{
		m_keys.erase(action);
	}
	else
	{
		throw std::runtime_error("THERE IS NO FUNCTION WITH THIS ASSOCIATION OF KEY AND ACTION");
	}
}

void hgui::KeyBoardManager::bind_key_callback(const std::variant<std::function<void()>, std::function<void(keys, actions)>>& function)
{
	m_keyCallback = function;
}

void hgui::KeyBoardManager::process()
{
	std::vector<std::function<void()>> toDo;
	for (auto& key : kernel::TextInput::m_focused.lock() ? m_apiBinds : decltype(m_apiBinds)(m_keys.begin(), m_keys.end()))
	{
		if (!key.first.index())
		{
			switch (const auto action = static_cast<actions>(glfwGetKey(glfwGetCurrentContext(),
				static_cast<int>(std::get<std::pair<keys, actions>>(key.first).
					first))))
			{
				case actions::PRESS:
					if (!key.second.first->is_counting())
					{
						key.second.first->start();
						if (action == std::get<std::pair<keys, actions>>(key.first).second && key.second.second)
						{
							toDo.push_back(key.second.second);
						}
					}
					break;
				case actions::RELEASE:
					if (key.second.first->is_counting())
					{
						key.second.first->reset();
						if (action == std::get<std::pair<keys, actions>>(key.first).second && key.second.second)
						{
							toDo.push_back(key.second.second);
						}
					}
					break;
				default:
					break;
			}
			if (std::get<std::pair<keys, actions>>(key.first).second == actions::REPEAT &&
			    key.second.first->get_time() >= 0.3 && key.second.second)
			{
				toDo.push_back(key.second.second);
			}
		}
		else
		{
			bool verify = true;
			for (const auto& keyCombination : std::get<std::pair<std::vector<keys>, actions>>(key.first).first)
			{
				if (static_cast<actions>(glfwGetKey(glfwGetCurrentContext(), static_cast<int>(keyCombination)))
				    != std::get<std::pair<std::vector<keys>, actions>>(key.first).second)
				{
					verify = false;
				}
			}
			switch (std::get<std::pair<std::vector<keys>, actions>>(key.first).second)
			{
				case actions::PRESS:
					if (!key.second.first->is_counting())
					{
						key.second.first->start();
						if (verify)
						{
							toDo.push_back(key.second.second);
						}
					}
					break;
				case actions::RELEASE:
					if (key.second.first->is_counting())
					{
						key.second.first->reset();
						if (verify)
						{
							toDo.push_back(key.second.second);
						}
					}
					break;
				default:
					break;
			}
			if (verify && key.second.first->get_time() >= 0.3 && key.second.second)
			{
				toDo.push_back(key.second.second);
			}
		}
	}
	for (const auto& function : toDo)
	{
		function();
	}
}

void hgui::KeyBoardManager::input([[maybe_unused]] GLFWwindow* window, int key, [[maybe_unused]] int scan, int action, [[maybe_unused]] int mods)
{
	if (const auto functionWithoutKeyInformation = std::get_if<std::function<void()>>(&m_keyCallback); functionWithoutKeyInformation && *functionWithoutKeyInformation)
	{
		(*functionWithoutKeyInformation)();
	}
	else if (const auto functionWithKeyInformation = std::get_if<std::function<void(keys, actions)>>(&m_keyCallback); functionWithKeyInformation && *functionWithKeyInformation)
	{
		(*functionWithKeyInformation)(static_cast<keys>(key), static_cast<actions>(action));
	}
}

void hgui::KeyBoardManager::add_bind(const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& action, const std::function<void()>& function)
{
	m_apiBinds.emplace_back(action, std::make_pair(std::make_shared<Timer>(), function));
}
