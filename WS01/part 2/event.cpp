/*****
 * OOP345-NAA Workshop 1 Part 2
 * Name: Tomas Rochwerger
 * Student Number: 159432210
 * Date: 01/22/2023
 *  I declare that this assignment is my own work in accordance with Seneca Academic Policy.
 *  No part of this assignment has been copied manually or electronically from any other source
 *  or distributed to other students.
 * */
#define _CRT_SECURE_NO_WARNINGS
#include "event.h"
#include <iostream>
#include <iomanip>
#include <cstring>

namespace seneca{
     size_t g_sysClock = 0u;

    Event::~Event() {
        delete[] m_desc;
    }

    Event::Event(const Event& src){
       *this = src;
    }

    Event &Event::operator=(const Event &src) {
        if (this != &src) {
            delete[] m_desc;
            m_desc = nullptr;
            m_time = src.m_time;
            if(src.m_desc != nullptr){
                m_desc = new char[strlen(src.m_desc)+1];
                strcpy(m_desc, src.m_desc);
            }
        }
        return *this;
    }

    void Event::display(){
        static int counter = 1;
        std::cout << std::setw(2) << std::setfill(' ') << counter << ". ";
        if (m_desc == nullptr) {
            std::cout << "| No Event |" << std::endl;
        } else {
            size_t hours = m_time / 3600;
            size_t minutes = (m_time % 3600) / 60;
            size_t secs = (m_time % 60);

            std::cout << std::setw(2) << std::setfill('0') << (hours) << ":"
                         << std::setw(2) << std::setfill('0') << (minutes) << ":"
                         << std::setw(2) << std::setfill('0') << (secs);
            std::cout << " => " << m_desc << std::endl;
        }
        ++counter;
    }
    void Event::set(const char *desc){
        delete[] m_desc;
        if (desc == nullptr) {
            m_desc = nullptr;
        } else {
            m_desc = new char[strlen(desc) + 1];
            strcpy(m_desc, desc);
            m_time = g_sysClock;
        }
    }

}