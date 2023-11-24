#include <ranges>
#include <hgui/header/TaskManager.h>

std::map<std::string, std::tuple<std::function<void()>, std::chrono::milliseconds, std::shared_ptr<hgui::Timer>>> hgui::TaskManager::m_tasks;

void hgui::TaskManager::program(const std::chrono::milliseconds& delay, const std::function<void()>& function, std::string id)
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
		throw std::runtime_error(("THERE IS ALREADY A TEXT AREA WITH THE ID : " + id).c_str());
	}
	timer->start();
}

void hgui::TaskManager::deprogram(const std::string& id)
{
	if (m_tasks.contains(id))
	{
		m_tasks.erase(id);
	}
	else
	{
		throw std::runtime_error(("THERE IS NO CANVAS WITH THE ID : " + id).c_str());
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
