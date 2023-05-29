#pragma once

#include "Include.h"
#include "Monitor.h"
#include "Tools.h"

namespace hgui
{
	namespace kernel
	{
		void resources_cleaner();
	}

	class MonitorManager
	{
	public:
		static const std::shared_ptr<kernel::Monitor>& get(const std::string& monitorName);
		static const std::vector<std::string> get_monitors_names();
		static const std::shared_ptr<kernel::Monitor>& get_primary_monitor();

	private:
		MonitorManager();

		static std::map<std::string, std::shared_ptr<kernel::Monitor>> m_monitors;

		static void init();

		friend void init();
		friend void kernel::resources_cleaner();
	};
}

