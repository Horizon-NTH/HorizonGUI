#pragma once

#include "Include.h"

namespace hgui
{
	class Timer
	{
	public:
		Timer();
		~Timer();

		void start();
		void stop();
		void reset();
		double get_time();	
		bool counting() const;

	private:
		bool m_counting;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
		std::chrono::duration<double> m_times;
	};
}

