#pragma once

#include "Include.h"

namespace hgui
{
	class Timer
	{
	public:
		Timer() noexcept;
		Timer(const Timer& timer) noexcept = default;
		Timer(Timer&& timer) noexcept = default;

		~Timer() noexcept = default;

		Timer& operator=(const Timer& timer) noexcept = default;
		Timer& operator=(Timer&& timer) noexcept = default;

		void start() noexcept;
		void stop() noexcept;
		void reset() noexcept;
		void restart() noexcept;

		[[nodiscard]] double get_time() const noexcept;
		[[nodiscard]] bool is_counting() const noexcept;

	private:
		bool m_counting;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
		mutable std::chrono::duration<double> m_times;
	};
}
