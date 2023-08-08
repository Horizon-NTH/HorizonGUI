#pragma once

#include "Include.h"
#include "Timer.h"

namespace hgui
{
	class TaskManager
	{
		friend class RenderManager;

	public:
		static void program(const std::chrono::milliseconds& delay, std::function<void()> function);

	private:
		TaskManager();

		static void process();

		static std::vector<std::tuple<std::function<void()>, std::chrono::milliseconds, std::shared_ptr<Timer>>> m_tasks;
	};
}