#include <hgui/header/KeyBoardManager.h>

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

std::map<std::variant<std::pair<hgui::keys, hgui::actions>, std::pair<std::vector<hgui::keys>, hgui::actions>>, std::pair<hgui::Timer, std::function<void()>>, hgui::kernel::VariantKeyComparator> hgui::KeyBoardManager::m_keys;
std::variant<std::function<void()>, std::function<void(hgui::keys, hgui::actions)>> hgui::KeyBoardManager::m_keyCallback([]{});

void hgui::KeyBoardManager::bind(const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& action, const std::function<void()>& function)
{
	if (!is_bind(action))
	{
		m_keys[action].second = function;
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
	for (auto& key : m_keys)
	{
		if (!key.first.index())
		{
			switch (const auto action = static_cast<actions>(glfwGetKey(glfwGetCurrentContext(),
				static_cast<int>(std::get<std::pair<keys, actions>>(key.first).
					first))))
			{
			case actions::PRESS:
				if (!key.second.first.is_counting())
				{
					key.second.first.start();
					if (action == std::get<std::pair<keys, actions>>(key.first).second && key.second.second)
					{
						toDo.push_back(key.second.second);
					}
				}
				break;
			case actions::RELEASE:
				if (key.second.first.is_counting())
				{
					key.second.first.reset();
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
				key.second.first.get_time() >= 0.3 && key.second.second)
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
			if (verify)
			{
				switch (std::get<std::pair<std::vector<keys>, actions>>(key.first).second)
				{
				case actions::PRESS:

					key.second.first.start();
					if (!key.first.index())
					{
						if (key.second.second)
						{
							toDo.push_back(key.second.second);
						}
					}
					break;
				case actions::RELEASE:
					if (key.second.first.is_counting())
					{
						key.second.first.reset();

						if (key.second.second)
						{
							toDo.push_back(key.second.second);
						}
					}
					break;
				case actions::REPEAT:
					if (key.second.first.get_time() >= 0.3 && key.second.second)
					{
						toDo.push_back(key.second.second);
					}
				default:
					break;
				}
			}
		}
	}
	for (const auto& function : toDo)
	{
		function();
	}
}

void hgui::KeyBoardManager::input(GLFWwindow* window, int key, int scan, int action, int mods)
{
	if (const auto function = std::get_if<std::function<void()>>(&m_keyCallback))
	{
		(*function)();
	}
	else if (const auto function2 = std::get_if<std::function<void(keys, actions)>>(&m_keyCallback))
	{
		(*function2)(static_cast<keys>(key), static_cast<actions>(action));
	}
}