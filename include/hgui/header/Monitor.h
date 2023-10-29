#pragma once

#include "Include.h"
#include "Maths.hpp"

namespace hgui::kernel
{
	class Monitor
	{
	public:
		explicit Monitor(GLFWmonitor* monitorPTR);

		[[nodiscard]] GLFWmonitor* get_monitor_ptr() const;
		[[nodiscard]] const size& get_size() const;
		[[nodiscard]] std::string get_name() const;
		[[nodiscard]] const point& get_position() const;

	private:
		GLFWmonitor* m_monitorPTR;
		size m_size;
		point m_position;
		std::string m_name;
	};
}
