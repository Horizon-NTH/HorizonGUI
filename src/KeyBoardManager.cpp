#include <hgui/header/KeyBoardManager.h>

bool hgui::kernel::VariantKeyComparator::operator()(const std::variant<std::pair<key::KeyBoardKey, key::Action>, std::pair<std::vector<key::KeyBoardKey>, key::Action>>& leftSide, const std::variant<std::pair<key::KeyBoardKey, key::Action>, std::pair<std::vector<key::KeyBoardKey>, key::Action>>& rightSide) const
{
	if (leftSide.index() == rightSide.index())
	{
		if (!leftSide.index())
		{
			std::pair<key::KeyBoardKey, key::Action> left = std::get<std::pair<key::KeyBoardKey, key::Action>>(leftSide);
			std::pair<key::KeyBoardKey, key::Action> right = std::get<std::pair<key::KeyBoardKey, key::Action>>(rightSide);
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
			std::pair<std::vector<key::KeyBoardKey>, key::Action> left = std::get<std::pair<std::vector<key::KeyBoardKey>, key::Action>>(leftSide);
			std::pair<std::vector<key::KeyBoardKey>, key::Action> right = std::get<std::pair<std::vector<key::KeyBoardKey>, key::Action>>(rightSide);
			int leftSum = std::accumulate(left.first.begin(), left.first.end(), 0);
			int rightSum = std::accumulate(right.first.begin(), right.first.end(), 0);
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

std::map<std::variant<std::pair<hgui::key::KeyBoardKey, hgui::key::Action>, std::pair<std::vector<hgui::key::KeyBoardKey>, hgui::key::Action>>, std::pair<hgui::Timer, std::function<void()>>, hgui::kernel::VariantKeyComparator> hgui::KeyBoardManager::m_keys;

void hgui::KeyBoardManager::bind(std::variant<std::pair<hgui::key::KeyBoardKey, hgui::key::Action>, std::pair<std::vector<hgui::key::KeyBoardKey>, hgui::key::Action>> action, std::function<void()> function)
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

void hgui::KeyBoardManager::unbind(std::variant<std::pair<hgui::key::KeyBoardKey, hgui::key::Action>, std::pair<std::vector<hgui::key::KeyBoardKey>, hgui::key::Action>> action)
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

void hgui::KeyBoardManager::process()
{
	for (auto& key : m_keys)
	{
		if (!key.first.index())
		{
			key::Action action = static_cast<key::Action>(glfwGetKey(WindowManager::get_current_windowPTR(), std::get<std::pair<key::KeyBoardKey, key::Action>>(key.first).first));
			switch (action)
			{
			case input::PRESS:
				if (!key.second.first.counting())
				{
					key.second.first.start();
					if (action == std::get<std::pair<key::KeyBoardKey, key::Action>>(key.first).second && key.second.second)
					{
						key.second.second();
					}
				}
				break;
			case input::RELEASE:
				if (key.second.first.counting())
				{
					key.second.first.reset();
					if (action == std::get<std::pair<key::KeyBoardKey, key::Action>>(key.first).second && key.second.second)
					{
						key.second.second();
					}

				}
				break;
			default:
				break;
			}
			if (std::get<std::pair<key::KeyBoardKey, key::Action>>(key.first).second == key::REPEAT && key.second.first.get_time() >= 0.3 && key.second.second)
			{
				key.second.second();
			}
		}
		else
		{
			bool verif = true;
			for (const auto& keyCombinason : std::get<std::pair<std::vector<key::KeyBoardKey>, key::Action>>(key.first).first)
			{
				if (!(glfwGetKey(WindowManager::get_current_windowPTR(), keyCombinason) == std::get<std::pair<std::vector<key::KeyBoardKey>, key::Action>>(key.first).second))
				{
					verif = false;
				}
			}
			if (verif)
			{
				switch (std::get<std::pair<std::vector<key::KeyBoardKey>, key::Action>>(key.first).second)
				{
				case input::PRESS:

					key.second.first.start();
					if (!key.first.index())
					{
						if (key.second.second)
						{
							key.second.second();
						}
					}
					break;
				case input::RELEASE:
					if (key.second.first.counting())
					{
						key.second.first.reset();

						if (key.second.second)
						{
							key.second.second();
						}

					}
					break;
				case key::REPEAT:
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