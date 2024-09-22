#ifndef SENECA_TIMEDTASK_H
#define SENECA_TIMEDTASK_H

#include <iostream>
#include <chrono>
#include <string>

namespace seneca
{
	constexpr int MAX_EVENTS = 10;
	class TimedTask {
		int m_cnt{ 0 };
		std::chrono::steady_clock::time_point m_timeStart;
		std::chrono::steady_clock::time_point m_timeEnd;
		struct Task {
			std::string m_description{};
			std::string m_timeUnit{};
			std::chrono::steady_clock::duration m_duration{};
		} m_events[MAX_EVENTS];
	public:
		void startClock();
		void stopClock();
		void addTask(const char*);
		friend std::ostream& operator<<(std::ostream& out, const TimedTask& task);
	};
}
#endif
