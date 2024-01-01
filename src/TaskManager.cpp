#include <ranges>
#include <hgui/header/TaskManager.h>

std::map<std::string, std::tuple<std::function<void()>, std::chrono::milliseconds, std::shared_ptr<hgui::Timer>>> hgui::TaskManager::m_tasks;

std::string hgui::TaskManager::program(const std::chrono::milliseconds& delay, const std::function<void()>& function, std::string id)
{
	static unsigned long long ids = 0;
	const auto timer = std::make_shared<Timer>();
	if (id.empty())
	{
		std::stringstream newID;
		newID << "HGUI_TASK_" << ids++;
		id = newID.str();
	}
	if (!m_tasks.contains(id))
	{
		m_tasks[id] = std::make_tuple(function, delay, timer);
	}
	else
	{
		throw std::runtime_error(("THERE IS ALREADY A TASK WITH THE ID : " + id).c_str());
	}
	timer->start();
	return std::move(id);
}

void hgui::TaskManager::deprogram(const std::variant<std::string, std::vector<std::string>>& tasks)
{
	if (const auto id = std::get_if<std::string>(&tasks))
	{
		if (m_tasks.contains(*id))
		{
			m_tasks.erase(*id);
		}
		else
		{
			throw std::runtime_error(("THERE IS NO TASK WITH THE ID : " + *id).c_str());
		}
	}
	else if (const auto ids = std::get_if<std::vector<std::string>>(&tasks))
	{
		for (const auto& identifiant : *ids)
		{
			if (m_tasks.contains(identifiant))
			{
				m_tasks.erase(identifiant);
			}
			else
			{
				throw std::runtime_error(("THERE IS NO TASK WITH THE ID : " + identifiant).c_str());
			}
		}
	}
}

std::vector<std::string> hgui::TaskManager::get_ids()
{
	std::vector<std::string> ids;
	ids.reserve(m_tasks.size());
	for (const auto& id : m_tasks | std::views::keys)
	{
		ids.push_back(id);
	}
	return ids;
}

void hgui::TaskManager::process()
{
	std::vector<std::string> taskToDo;
	for (const auto& [id, task] : m_tasks)
	{
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<double>(std::get<2>(task)->get_time()))
		    >= std::get<1>(task))
		{
			taskToDo.push_back(id);
		}
	}
	for (const auto& id : taskToDo)
	{
		std::get<0>(m_tasks[id])();
		m_tasks.erase(id);
	}
}
