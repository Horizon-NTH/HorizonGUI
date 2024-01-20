#pragma once

#include "Coordinate.hpp"

namespace hgui::kernel
{
	class Monitor
	{
	public:
		explicit Monitor(GLFWmonitor* monitorPTR);
		Monitor(const Monitor& monitor) noexcept = default;
		Monitor(Monitor&& monitor) noexcept = default;

		~Monitor() noexcept = default;

		Monitor& operator=(const Monitor& monitor) noexcept = default;
		Monitor& operator=(Monitor&& monitor) noexcept = default;

		[[nodiscard]] GLFWmonitor* get_monitor_ptr() const noexcept;
		[[nodiscard]] const size& get_size() const noexcept;
		[[nodiscard]] std::string get_name() const noexcept;
		[[nodiscard]] const point& get_position() const noexcept;

	private:
		GLFWmonitor* m_monitorPTR;
		size m_size;
		point m_position;
		std::string m_name;
	};
}
