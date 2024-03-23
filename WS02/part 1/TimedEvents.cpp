//
// Created by Tomas Rochwerger on 2024-01-23.
//

#include "TimedEvents.h"
#include <iomanip>

namespace seneca {

    void TimedEvents::startClock() {
        m_startTime = std::chrono::steady_clock::now();
    }

    void TimedEvents::stopClock() {
        m_endTime = std::chrono::steady_clock::now();
    }

    void TimedEvents::addEvent(const char *desc) {
        if(m_eventNum < MAX_EVENTS){
            // or (desc != null && desc[0]!='\0')
            if(!desc){
                m_events[m_eventNum].e_name = nullptr;
            } else {
                m_events[m_eventNum].e_name = desc;
                m_events[m_eventNum].e_units = "nanoseconds";
            }
        }
    }

    std::ostream& operator<<(std::ostream& os, const TimedEvents& te){
        os << "Execution Times:" << endl;
        os << "--------------------------" << endl;
        for(auto i : te.m_events) {
            os << setw(21) << left << i.e_name;
            os << setw(13) << right << i.e_duration.count() << " " << i.e_units << endl;
        }
        os << "--------------------------" << endl;
        return os;
    };
} // seneca