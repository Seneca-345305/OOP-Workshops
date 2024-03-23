// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 2024-02-09
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "Child.h"
#include <iostream>

namespace seneca {
    // Constructor
    Child::Child(std::string name, int age, const Toy* toys[], size_t count)
            : m_name(std::move(name)), m_age(age), m_numToys(count) {
        // Deep copy of the array of pointers
        // Allocates memory for the array of pointers
        m_toys = new const Toy*[m_numToys];
        for (size_t i = 0; i < m_numToys; ++i) {
            // Make a deep copy of each Toy
            m_toys[i] = new Toy(*toys[i]);
        }
    }

    // Destructor
    Child::~Child() {
        for (size_t i = 0; i < m_numToys; ++i) {
            delete m_toys[i];
        }
        delete[] m_toys;
    }

    // Copy constructor
    Child::Child(const Child& other)
            : m_name(other.m_name), m_age(other.m_age), m_numToys(other.m_numToys) {
        // Deep copy of the array of pointers
        m_toys = new const Toy*[m_numToys];
        for (size_t i = 0; i < m_numToys; ++i) {
            // Make a deep copy of each Toy
            m_toys[i] = new Toy(*other.m_toys[i]);
        }
    }

    // Copy assignment operator
    Child& Child::operator=(const Child& other) {
        // Check for self-assignment
        if (this != &other) {
            // cleanup
            for (size_t i = 0; i < m_numToys; ++i) {
                delete m_toys[i];
            }
            delete[] m_toys;

            // Copy from source
            m_name = other.m_name;
            m_age = other.m_age;
            m_numToys = other.m_numToys;

            // Deep copy of the array of pointers
            m_toys = new const Toy*[m_numToys];
            for (size_t i = 0; i < m_numToys; ++i) {
                // Make a deep copy of each Toy
                m_toys[i] = new Toy(*other.m_toys[i]);
            }
        }
        return *this;
    }

    // Move constructor
    Child::Child(Child&& other) noexcept
            : m_name(std::move(other.m_name)), m_age(other.m_age), m_toys(other.m_toys), m_numToys(other.m_numToys) { // Transfer ownership of m_toys to this object

        // Reset the source object
        other.m_toys = nullptr;
        other.m_numToys = 0;
        other.m_age = 0;
    }

    // Move assignment operator
    Child& Child::operator=(Child&& other) noexcept {
        // Check for self-assignment
        if (this != &other) {
            // cleanup
            for (size_t i = 0; i < m_numToys; ++i) {
                delete m_toys[i];
            }
            delete[] m_toys;

            // Transfer ownership of m_toys to this object
            m_name = std::move(other.m_name);
            m_age = other.m_age;
            m_toys = other.m_toys;
            m_numToys = other.m_numToys;

            // Reset the source object
            other.m_toys = nullptr;
            other.m_numToys = 0;
            other.m_age = 0;
        }
        return *this;
    }

    // Friend Helper
    std::ostream& operator<<(std::ostream& os, const Child& child) {
        static int callCount = 0;
        callCount++;

        printLine(os);
        os << "Child " << callCount << ": " << child.m_name << " " << child.m_age << " years old:\n";
        printLine(os);

        if (child.m_numToys == 0) {
            os << "This child has no toys!\n";
        } else {
            for (size_t i = 0; i < child.m_numToys; i++) {
                os << *child.m_toys[i];
            }
        }

        printLine(os);
        return os;
    }

} // namespace seneca