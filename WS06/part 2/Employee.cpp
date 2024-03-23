// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 03/10/2024
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "Employee.h"
#include "Utilities.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

namespace seneca {

    Employee::Employee(std::istream& in) {
        std::string tag, name, age, id;

        std::getline(in, tag, ',');
        std::getline(in, name, ',');
        std::getline(in, age, ',');
        std::getline(in, id, ',');

        name = trim(name);
        id = trim(id);

        if (!std::all_of(age.begin(), age.end(), ::isdigit)) {
            std::string err = name + "++Invalid record!";
            throw(err);
        } else if (id[0] != 'E') {
            std::string err = name + "++Invalid record!";
            throw (err);
        }

        m_id = id[0];
        auto temp = id.substr(1);
        for (auto c : temp) {
            if (std::isdigit(c)) {
                //write only the digits to the id (after the first character)
                m_id += c;
            }
        }

        m_name = name;
        m_age = std::stoi(age);
    }

    void Employee::display(std::ostream &out) const {
        out << "| " << std::left << std::setw(10)
         << "Employee" << "| "
            << std::setw(10) << id() << "| "
            << std::setw(20) << name() << " | "
            << std::setw(3) << age() << " |";
    }
}