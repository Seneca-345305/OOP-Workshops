//
// Created by Tomas Rochwerger on 2024-01-23.
//

#ifndef WS02_TIMEDEVENTS_H
#define WS02_TIMEDEVENTS_H
#include <string>
#include <chrono>
#

using namespace std;
namespace seneca {
    class TimedEvents {
        static const size_t MAX_EVENTS = 10;
        std::chrono::steady_clock::time_point m_startTime;
        std::chrono::steady_clock::time_point m_endTime;
        struct Event {
            char* e_name{};
            char* e_units{};
            chrono::steady_clock::duration e_duration{};
        } m_events[MAX_EVENTS]{};
        size_t m_eventNum{};
    public:
        TimedEvents(){};
        void startClock();
        void stopClock();
        void addEvent(const char* desc);
        friend std::ostream& operator<<(std::ostream& os, const TimedEvents& te);

    };

} // seneca

#endif //WS02_TIMEDEVENTS_H
