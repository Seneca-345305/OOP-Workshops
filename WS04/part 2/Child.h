// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 2024-02-09
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SENECA_CHILD_H
#define SENECA_CHILD_H

#include "Toy.h"
#include <string>

namespace seneca {

    class Child {
        std::string m_name;
        unsigned short m_age;
        const Toy** m_toys;
        size_t m_numToys;

    public:
        // Constructor with 3 parameters
        Child(std::string name, int age, const Toy* toys[], size_t count);

        // Copy constructor
        Child(const Child& other);

        // Copy assignment operator
        Child& operator=(const Child& other);

        // Move constructor
        Child(Child&& other) noexcept;

        // Move assignment operator
        Child& operator=(Child&& other) noexcept;
        ~Child();

        // Output operator
        friend std::ostream& operator<<(std::ostream& os, const Child& child);
    };

} // namespace seneca

#endif //SENECA_CHILD_H