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
		TaskManager(const TaskManager& bufferManager) = delete;
		TaskManager(TaskManager&& bufferManager) = delete;

		TaskManager& operator=(const TaskManager& bufferManager) = delete;
		TaskManager& operator=(TaskManager&& bufferManager) = delete;

		static void program(const std::chrono::milliseconds& delay, std::function<void()> function);

	private:
		static void process();

		static std::vector<std::tuple<std::function<void()>, std::chrono::milliseconds, std::shared_ptr<Timer>>> m_tasks;
	};
}
