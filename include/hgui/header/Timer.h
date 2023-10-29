#pragma once

#include "Include.h"

namespace hgui
{
	class Timer
	{
	public:
		Timer();

		~Timer() = default;

		void start();

		void stop();

		void reset();

		[[nodiscard]] double get_time() const;

		[[nodiscard]] bool is_counting() const;

	private:
		bool m_counting;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
		mutable std::chrono::duration<double> m_times;
	};
}
