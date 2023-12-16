#pragma once

#include "Include.h"
#include "Timer.h"

namespace hgui
{
	class TaskManager
	{
		friend class Renderer;

	public:
		TaskManager() = delete;
		~TaskManager() = delete;
		TaskManager(const TaskManager& taskManager) = delete;
		TaskManager(TaskManager&& taskManager) = delete;

		TaskManager& operator=(const TaskManager& taskManager) = delete;
		TaskManager& operator=(TaskManager&& taskManager) = delete;

		static void program(const std::chrono::milliseconds& delay, const std::function<void()>& function, std::string id = "");
		static void deprogram(const std::string& id);

		static std::vector<std::string> get_ids();

	private:
		static void process();

		static std::map<std::string, std::tuple<std::function<void()>, std::chrono::milliseconds, std::shared_ptr<Timer>>> m_tasks;
	};
}