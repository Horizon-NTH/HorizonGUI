#include <hgui/header/Timer.h>

hgui::Timer::Timer() : m_counting(false),
                       m_times(0.0)
{}

void hgui::Timer::start()
{
	m_startTime = std::chrono::high_resolution_clock::now();
	m_counting = true;
}

void hgui::Timer::stop()
{
	m_times = std::chrono::high_resolution_clock::now() - m_startTime;
	m_counting = false;
}

void hgui::Timer::reset()
{
	m_times = m_startTime - m_startTime;
	m_counting = false;
}

double hgui::Timer::get_time() const
{
	if (m_counting)
	{
		m_times = std::chrono::high_resolution_clock::now() - m_startTime;
	}
	return m_times.count();
}

bool hgui::Timer::is_counting() const
{
	return m_counting;
}
