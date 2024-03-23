//
// Created by Tomas  on 2024-03-07.
//

#ifndef SENECA_COLLEGE_H
#define SENECA_COLLEGE_H
#include "Person.h"
#include <vector>
#include <iostream>
#include <iomanip>

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
    };

} // seneca

#endif //SENECA_COLLEGE_H
