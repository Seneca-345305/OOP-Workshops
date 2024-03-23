// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 03/10/2024
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "Student.h"
#include "Utilities.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

namespace seneca {
    Student::Student(std::istream &in) {
        std::string tag, name, age, id, count;
        std::string* courses;

        std::getline(in, tag, ',');
        std::getline(in, name, ',');
        std::getline(in, age, ',');

        name = trim(name);
        age = trim(age);

        if (!std::all_of(age.begin(), age.end(), ::isdigit)) {
            std::string err = name + "++Invalid record!";
            throw(err);
        }

        std::getline(in, id, ',');
        id = trim(id);

        if (id[0] != 'S') {
            std::string err = name + "++Invalid record!";
            throw(err);
        }

        std::getline(in, count, ',');
        courses = new std::string[std::stoi(count)];
        for (auto i = 0; i < std::stoi(count); i++) {
            std::getline(in, courses[i], ',');
        }

        for (auto i = 0; i < std::stoi(count); i++) {
            courses[i] = trim(courses[i]);
        }

        m_name = name;
        m_age = age;
        m_id = id;
        m_courses = courses;
        m_count = std::stoi(count);
    }

    void Student::display(std::ostream &out) const {
        out << "| " << std::left << std::setw(10)
            << status() << "| "
            << std::setw(10) << id() << "| "
            << std::setw(20) << name() << " | "
            << std::setw(3) << age() << " |";
        for (size_t i = 0; i < m_count; i++) {
            out << m_courses[i];
            if (i != m_count - 1) {
                out << ", ";
            }
        }
    }
}