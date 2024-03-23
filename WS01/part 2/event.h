/*****
 * OOP345-NAA Workshop 1 Part 2
 * Name: Tomas Rochwerger
 * Student Number: 159432210
 * Date: 01/22/2023
 *  I declare that this assignment is my own work in accordance with Seneca Academic Policy.
 *  No part of this assignment has been copied manually or electronically from any other source
 *  or distributed to other students.
 * */

#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H
#include <iostream>
namespace seneca {
    extern size_t g_sysClock;
    class Event {
//        Part 1:
//        char description[128]{};
        char* m_desc{};
        size_t m_time{};
    public:
        Event() = default;
        Event(const Event& src);
        ~Event();
        void display();
        void set(const char* desc = nullptr);
        Event& operator=(const Event& src);
    };
} // seneca

#endif //SENECA_EVENT_H
