// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 03/10/2024
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


#ifndef SENECA_COLLEGE_H
#define SENECA_COLLEGE_H
#include "Person.h"
#include <vector>
#include <iostream>
#include <list>

namespace seneca {

    class College {
    private:
        std::vector<Person*> m_persons;

    public:
        College() = default;
        ~College();

        // Disable copy operations
        College(const College&) = delete;
        College& operator=(const College&) = delete;

        // Add a person to the college
        College& operator+=(Person* thePerson);

        // Display all persons in the college
        void display(std::ostream& out) const;

        // Select function
        template <typename T>
        void select(const T& test, std::list<const Person*>& persons) {
            for (const auto& person : m_persons) {
                if (test(person)) {
                    persons.push_back(person);
                }
            }
        }
    };

}

#endif //SENECA_COLLEGE_H
