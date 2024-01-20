#pragma once

#include "Include.h"

namespace hgui
{
	class Timer;

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

		static std::string program(const std::chrono::milliseconds& delay, const std::function<void()>& function, std::string id = "");
		static bool is_program(const std::string& id);
		static void deprogram(const std::variant<std::string, std::vector<std::string>>& tasks = get_ids());

		[[nodiscard]] static std::vector<std::string> get_ids();

	private:
		static void process();

		inline static std::map<std::string, std::tuple<std::function<void()>, std::chrono::milliseconds, std::shared_ptr<Timer>>> m_tasks{};
	};
}
