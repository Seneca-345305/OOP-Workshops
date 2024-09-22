#include <iomanip>
#include "TimedTask.h"

namespace seneca
{
	// start timer
	//
	void TimedTask::startClock()
	{
		m_timeStart = std::chrono::steady_clock::now();
	}

	// stop timer
	//
	void TimedTask::stopClock()
	{
		m_timeEnd = std::chrono::steady_clock::now();
	}

	// record an event
	//
	void TimedTask::addTask(const char* msg)
	{
		auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(m_timeEnd - m_timeStart);
		if (m_cnt < MAX_EVENTS)
		{
			this->m_events[m_cnt].m_description = msg;
			this->m_events[m_cnt].m_timeUnit = "nanoseconds";
			this->m_events[m_cnt].m_duration = ms;
			m_cnt++;
		}
	}

	// report the set of times recorded
	// 
	std::ostream& operator<<(std::ostream& out, const TimedTask& task)
	{
		out << "--------------------------\n";
		out << "Execution Times:\n";
		out << "--------------------------\n";
		for (int i = 0; i < task.m_cnt; i++)
			out << std::setw(21) << std::left
			<< task.m_events[i].m_description << ' ' << std::setw(13) << std::right
			<< task.m_events[i].m_duration.count() << ' '
			<< task.m_events[i].m_timeUnit << '\n';
		out << "--------------------------\n";
		return out;
	}
}
