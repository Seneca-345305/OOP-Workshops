// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 03/10/2024
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "Professor.h"
#include "Utilities.h"
#include <iostream>

namespace seneca {
    Professor::Professor(std::istream &in) : Employee(in) {
        std::string department{};
        std::getline(in, department, '\n');
        department = trim(department);
        m_department = department;
    }

    void Professor::display(std::ostream &out) const {
        Employee::display(out);
        if (status() == "Professor") {
            out  << department() << "|";
            out << " "<< status();
        }

    }
}