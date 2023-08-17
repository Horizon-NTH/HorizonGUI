#include <hgui/header/KeyBoardManager.h>

bool hgui::kernel::VariantKeyComparator::operator()(const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& leftSide, const std::variant<std::pair<keys, actions>, std::pair<std::vector<keys>, actions>>& rightSide) const
{
	if (leftSide.index() == rightSide.index())
	{
		if (!leftSide.index())
		{
			std::pair<keys, actions> left = std::get<std::pair<keys, actions>>(leftSide);
			std::pair<keys, actions> right = std::get<std::pair<keys, actions>>(rightSide);
			if (left.first == right.first)
			{
				return left.second < right.second;
			}
			else
			{
				return left.first < right.first;
			}
		}
		else
		{
			std::pair<std::vector<keys>, actions> left = std::get<std::pair<std::vector<keys>, actions>>(leftSide);
			std::pair<std::vector<keys>, actions> right = std::get<std::pair<std::vector<keys>, actions>>(rightSide);
			int leftSum = std::accumulate(left.first.begin(), left.first.end(), 0, [](const int& sum, const keys& value) 
				{
					return sum + static_cast<int>(value); 
				});
			int rightSum = std::accumulate(right.first.begin(), right.first.end(), 0, [](const int& sum, const keys& value) 
				{
					return sum + static_cast<int>(value);
				});
			if (leftSum == rightSum)
			{
				return left.second < right.second;
			}
			else
			{
				return leftSum < rightSum;
			}
		}
	}
	else
	{
		return leftSide.index() < rightSide.index();
	}
}

std::map<std::variant<std::pair<hgui::keys, hgui::actions>, std::pair<std::vector<hgui::keys>, hgui::actions>>, std::pair<hgui::Timer, std::function<void()>>, hgui::kernel::VariantKeyComparator> hgui::KeyBoardManager::m_keys;
std::variant<std::function<void()>, std::function<void(hgui::keys, hgui::actions)>> hgui::KeyBoardManager::m_keyCallback([]() {});

void hgui::KeyBoardManager::bind(const std::variant<std::pair<hgui::keys, hgui::actions>, std::pair<std::vector<hgui::keys>, hgui::actions>>& action, const std::function<void()>& function)
{
	if (m_keys.find(action) == m_keys.end())
	{
		m_keys[action].second = function;
	}
	else
	{
		throw std::exception("THERE IS ALREADY A FUNCTION WITH THIS ASSOCIATION OF KEY AND ACTION");
	}
}

void hgui::KeyBoardManager::unbind(const std::variant<std::pair<hgui::keys, hgui::actions>, std::pair<std::vector<hgui::keys>, hgui::actions>>& action)
{
	if (m_keys.find(action) != m_keys.end())
	{
		m_keys.erase(action);
	}
	else
	{
		throw std::exception("THERE IS NO FUNCTION WITH THIS ASSOCIATION OF KEY AND ACTION");
	}
}

void hgui::KeyBoardManager::bind_keycallback(const std::variant<std::function<void()>, std::function<void(keys, actions)>>& function)
{
	m_keyCallback = function;
}

void hgui::KeyBoardManager::process()
{
	for (auto& key : m_keys)
	{
		if (!key.first.index())
		{
			actions action = static_cast<actions>(glfwGetKey(glfwGetCurrentContext(), 
				static_cast<int>(std::get<std::pair<keys, actions>>(key.first).first)));
			switch (action)
			{
			case actions::PRESS:
				if (!key.second.first.is_counting())
				{
					key.second.first.start();
					if (action == std::get<std::pair<keys, actions>>(key.first).second && key.second.second)
					{
						key.second.second();
					}
				}
				break;
			case actions::RELEASE:
				if (key.second.first.is_counting())
				{
					key.second.first.reset();
					if (action == std::get<std::pair<keys, actions>>(key.first).second && key.second.second)
					{
						key.second.second();
					}

				}
				break;
			default:
				break;
			}
			if (std::get<std::pair<keys, actions>>(key.first).second == actions::REPEAT &&
				key.second.first.get_time() >= 0.3 && key.second.second)
			{
				key.second.second();
			}
		}
		else
		{
			bool verif = true;
			for (const auto& keyCombinason : std::get<std::pair<std::vector<keys>, actions>>(key.first).first)
			{
				if (!(static_cast<actions>(glfwGetKey(glfwGetCurrentContext(), static_cast<int>(keyCombinason))) 
					== std::get<std::pair<std::vector<keys>, actions>>(key.first).second))
				{
					verif = false;
				}
			}
			if (verif)
			{
				switch (std::get<std::pair<std::vector<keys>, actions>>(key.first).second)
				{
				case actions::PRESS:

					key.second.first.start();
					if (!key.first.index())
					{
						if (key.second.second)
						{
							key.second.second();
						}
					}
					break;
				case actions::RELEASE:
					if (key.second.first.is_counting())
					{
						key.second.first.reset();

						if (key.second.second)
						{
							key.second.second();
						}

					}
					break;
				case actions::REPEAT:
					if (key.second.first.get_time() >= 0.3 && key.second.second)
					{
						key.second.second();
					}
				default:
					break;
				}
			}
		}
	}
}

void hgui::KeyBoardManager::input(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (auto function = std::get_if<std::function<void()>>(&m_keyCallback))
	{
		(*function)();
	}
	else if (auto function = std::get_if<std::function<void(keys, actions)>>(&m_keyCallback))
	{
		(*function)(static_cast<keys>(key), static_cast<actions>(action));
	}
}