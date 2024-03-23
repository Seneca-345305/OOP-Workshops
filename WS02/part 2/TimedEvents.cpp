// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 01/29/2024
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.

#include "TimedEvents.h"
#include <iostream>
#include <iomanip>

namespace seneca {

    void TimedEvents::startClock() {
        // start the clock and store in m_startTime
        m_startTime = std::chrono::steady_clock::now();
    }

    void TimedEvents::stopClock() {
        // stop the clock and store in m_endTime
        m_endTime = std::chrono::steady_clock::now();
    }

    void TimedEvents::addEvent(const char *desc) {
        // if the event is not empty, store the event in the array of events
        if(m_eventNum < MAX_EVENTS){
            // if the description is empty, set the event name and units to nullptr
            if(!desc){
                m_events[m_eventNum].e_name = nullptr;
                m_events[m_eventNum].e_units = nullptr;
            } else {
                // if the description is not empty, store the event name and units
                m_events[m_eventNum].e_name = desc;
                m_events[m_eventNum].e_units = "nanoseconds";
                // store duration using duration_cast
                m_events[m_eventNum].e_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(m_endTime - m_startTime);
                ++m_eventNum;
            }
        }
    }

    std::ostream& operator<<(std::ostream& os, const TimedEvents& te){
        os << "--------------------------" << std::endl;
        os << "Execution Times:" << std::endl;
        os << "--------------------------" << std::endl;

        for(size_t i = 0; i < te.m_eventNum; ++i){
            os << std::setw(21) << std::left << te.m_events[i].e_name << " ";
            os << std::setw(13) << std::right << te.m_events[i].e_duration.count() << " " << te.m_events[i].e_units << std::endl;
        }
        os << "--------------------------" << std::endl;
        return os;
    };
} // seneca