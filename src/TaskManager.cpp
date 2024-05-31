#include "../include/hgui/header/TaskManager.h"
#include "../include/hgui/header/Timer.h"

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
		m_insertionOrder.push_back(id);
	}
	else
	{
		throw std::runtime_error("THERE IS ALREADY A TASK WITH THE ID : " + id);
	}
	timer->start();
	return std::move(id);
}

bool hgui::TaskManager::is_program(const std::string& id)
{
	return m_tasks.contains(id);
}

void hgui::TaskManager::deprogram(const std::variant<std::string, std::vector<std::string>>& tasks)
{
	if (const auto id = std::get_if<std::string>(&tasks))
	{
		if (m_tasks.contains(*id))
		{
			m_tasks.erase(*id);
			m_insertionOrder.erase(std::ranges::find(m_insertionOrder, *id));
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
				m_insertionOrder.erase(std::ranges::find(m_insertionOrder, identifiant));
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
	return m_insertionOrder;
}

void hgui::TaskManager::process()
{
	std::vector<std::string> taskToDo;
	for (const auto& id : m_insertionOrder)
	{
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<double>(std::get<2>(m_tasks[id])->get_time()))
		    >= std::get<1>(m_tasks[id]))
		{
			taskToDo.push_back(id);
		}
	}
	for (const auto& id : taskToDo)
	{
		if (!m_tasks.contains(id))
			continue;
		std::get<0>(m_tasks[id])();
		m_tasks.erase(id);
		if (const auto it = std::ranges::find(m_insertionOrder, id); it != m_insertionOrder.end())
			m_insertionOrder.erase(it);
	}
}
