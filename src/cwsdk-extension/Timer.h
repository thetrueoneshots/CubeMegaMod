#pragma once
#include <time.h>

namespace cube
{
	class Timer
	{
	private:
		time_t m_Time;
		double m_Interval;
	public:
		Timer() {}
		Timer(double interval, time_t start = 0) : m_Time(start), m_Interval(interval) {}
		~Timer() {}

		bool IsTriggered(time_t time, bool reset = true)
		{
			double seconds = difftime(time, m_Time);
			if (seconds < m_Interval)
			{
				return false;
			}

			if (reset)
			{
				m_Time = time;
			}
			return true;
		}
	};
}