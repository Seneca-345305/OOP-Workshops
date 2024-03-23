// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 03/10/2024
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "College.h"
#include "Person.h"
#include <iomanip>

namespace seneca {
    // Add a person to the college
    College &College::operator+=(Person *thePerson) {
        m_persons.push_back(thePerson);
        return *this;
    }

    // Display all persons in the college
    void College::display(std::ostream &out) const {
        out << "------------------------------------------------------------------------------------------------------------------------\n";
        out << "|                                        Test #1 Persons in the college!                                               |\n";
        out << "------------------------------------------------------------------------------------------------------------------------\n";
        for (const auto& person : m_persons) {
            person->display(out);
            out << '\n';
        }

        out << "------------------------------------------------------------------------------------------------------------------------\n";
        out << "|                                        Test #2 Persons in the college!                                               |\n";
        out << "------------------------------------------------------------------------------------------------------------------------\n";
        for (const auto& person : m_persons) {
            std::cout.setf(std::ios::left);
            out << "| " << std::setw(10) << person->status() << "| "
                << std::setw(10) << person->id() << "| "
                << std::setw(20) << person->name() << " | "
                << std::setw(3) << person->age() << " |" << '\n';
        }
        out << "------------------------------------------------------------------------------------------------------------------------\n";
    }

    College::~College() {
        for (auto& person : m_persons) {
            delete person;
        }
    }



}