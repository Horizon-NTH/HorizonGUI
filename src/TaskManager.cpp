#include <hgui/header/TaskManager.h>

std::vector<std::tuple<std::function<void()>, std::chrono::milliseconds, std::shared_ptr<hgui::Timer>>> hgui::TaskManager::m_tasks;

void hgui::TaskManager::program(const std::chrono::milliseconds& delay, const std::function<void()>& function)
{
	auto timer = std::make_shared<Timer>();
	m_tasks.push_back({ function, delay, timer });
	timer->start();
}

void hgui::TaskManager::process()
{
	std::vector<std::function<void()>> taskToDo;
	for (auto it = m_tasks.begin(); it != m_tasks.end();)
	{
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<double>(std::get<2>(*it)->get_time())) 
			>= std::get<1>(*it))
		{
			taskToDo.push_back(std::get<0>(*it));
			it = m_tasks.erase(it);
		}
		else
		{
			it++;
		}
	}
	for (auto& task : taskToDo)
	{
		task();
	}
}
