#pragma once

#include "Include.h"
#include "Define.h"
#include "Monitor.h"

namespace hgui
{
	class MonitorManager
	{
	public:
		MonitorManager() = delete;
		~MonitorManager() = delete;
		MonitorManager(const MonitorManager& monitorManager) = delete;
		MonitorManager(MonitorManager&& monitorManager) = delete;

		MonitorManager& operator=(const MonitorManager& monitorManager) = delete;
		MonitorManager& operator=(MonitorManager&& monitorManager) = delete;

		[[nodiscard]] static const std::shared_ptr<kernel::Monitor>& get(const std::string& monitorName);
		[[nodiscard]] static std::vector<std::string> get_monitors_names();
		[[nodiscard]] static const std::shared_ptr<kernel::Monitor>& get_primary_monitor();

	private:
		static std::map<std::string, std::shared_ptr<kernel::Monitor>> m_monitors;

		static void init();

		friend void init();
		friend void kernel::resources_cleaner();
	};
}