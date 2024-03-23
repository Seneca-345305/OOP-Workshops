//
// Created by Tomas  on 2024-03-07.
//

#include "Employee.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

namespace seneca {

    Employee::Employee(std::istream& in) {
        std::string tag, name, age, id;

        std::getline(in, tag, ',');
        std::getline(in, name, ',');
        std::getline(in, age, ',');
        std::getline(in, id, '\n');

        // Remove leading and trailing spaces
        name.erase(0, name.find_first_not_of(' '));
        name.erase(name.find_last_not_of(' ') + 1);
        id.erase(0, id.find_first_not_of(' '));
        id.erase(id.find_last_not_of(' ') + 1);

//        if (tag != "e" && tag != "E") {
//            throw std::runtime_error(name + "++Invalid record!");
//        }
        if (!std::all_of(age.begin(), age.end(), ::isdigit)) {
            std::string err = name + "++Invalid record!";
            throw(err);
        }
        if (id[0] != 'E') {
            std::string err = name + "++Invalid record!";
            throw(err);
        }


        m_name = name;
        m_age = std::stoi(age);
        m_id = id;
    }

    void Employee::display(std::ostream &out) const {
        out << "| " << std::left << std::setw(10)
         << status() << "| "
            << std::setw(10) << m_id << "| "
            << std::setw(20) << m_name << " | "
            << std::setw(3) << m_age << " |";
    }
} // seneca