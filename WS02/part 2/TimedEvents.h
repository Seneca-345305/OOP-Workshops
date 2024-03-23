// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 01/29/2024
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.

#ifndef SENECA_TIMEDEVENTS_H
#define SENECA_TIMEDEVENTS_H
#include <string>
#include <chrono>

namespace seneca {
    class TimedEvents {
        static const size_t MAX_EVENTS = 10;
        std::chrono::steady_clock::time_point m_startTime;
        std::chrono::steady_clock::time_point m_endTime;
        struct Event {
            std::string e_name{};
            std::string e_units{};
            std::chrono::steady_clock::duration e_duration{};
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

#endif //SENECA_TIMEDEVENTS_H
