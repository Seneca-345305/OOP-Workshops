// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 2024-02-09
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "ConfirmOrder.h"

namespace seneca {

    //Copy constructor
    ConfirmOrder::ConfirmOrder(const ConfirmOrder &src) : m_numToys(src.m_numToys) {
        if(src.m_toys == nullptr) {
            m_toys = nullptr;
        } else {
            // Deep copy of the array of pointers
            // Allocates memory for the array of pointers
            m_toys = new const Toy*[m_numToys];
            for (size_t i = 0; i < m_numToys; i++) {
                // Only copy the pointer
                m_toys[i] = src.m_toys[i];
            }
        }
    }

    // Destructor
    ConfirmOrder::~ConfirmOrder() {
        delete[] m_toys;  // Only delete the array of pointers
    }

    // Copy assignment operator
    ConfirmOrder &ConfirmOrder::operator=(const ConfirmOrder &src) {
        // Check for self-assignment
        if (this != &src) {
            // Delete old memory
            for (size_t i = 0; i < m_numToys; ++i) {
                delete m_toys[i];
            }
            // cleanup
            delete[] m_toys;

            // Copy from source
            m_numToys = src.m_numToys;
            m_toys = new const Toy*[m_numToys];
            for (size_t i = 0; i < m_numToys; i++) {
                // Make a deep copy of each Toy
                m_toys[i] = new Toy(*src.m_toys[i]);
            }
        }
        return *this;
    }

    // Move constructor
    ConfirmOrder::ConfirmOrder(ConfirmOrder &&src) noexcept : m_toys(src.m_toys), m_numToys(src.m_numToys) {
        src.m_toys = nullptr;
        src.m_numToys = 0;
    }

    // Move assignment operator
    ConfirmOrder &ConfirmOrder::operator=(ConfirmOrder &&src) noexcept {
        // Check for self-assignment
        if (this != &src) {
            // cleanup
            delete[] m_toys;

            // Move from source
            m_toys = src.m_toys;
            m_numToys = src.m_numToys;

            // Reset source
            src.m_toys = nullptr;
            src.m_numToys = 0;
        }
        return *this;
    }

    // Add a toy to the list of confirmations
    ConfirmOrder &ConfirmOrder::operator+=(const Toy &toy) {
        // Check if the toy is already in the list
        for (size_t i = 0; i < m_numToys; i++) {
            if (m_toys[i] == &toy) {
                return *this;
            }
        }

        // Add the toy to the list
        // Allocate memory for the new array of pointers to toys(pointer to pointer)
        const Toy **newToys = new const Toy*[m_numToys + 1];

        for (size_t i = 0; i < m_numToys; i++) {
            // Copy the pointer
            newToys[i] = m_toys[i];
        }

        // Add the new toy
        newToys[m_numToys] = &toy;

        // cleanup
        delete[] m_toys;
        // Update the pointer to the new array
        m_toys = newToys;
        m_numToys++;

        return *this;
    }

    // Remove a toy from the list of confirmations
    ConfirmOrder &ConfirmOrder::operator-=(const Toy &toy) {
        for (size_t i = 0; i < m_numToys; i++) {
            if (m_toys[i] == &toy) {
                m_toys[i] = nullptr;
                return *this;
            }
        }
        return *this;
    }


    // Output operator
    std::ostream &operator<<(std::ostream &os, const ConfirmOrder &order) {

        printLine(os);
        os << "Confirmations to Send\n";
        printLine(os);

        if (order.m_numToys == 0) {
            os << "There are no confirmations to send!\n";
        } else {
            for (size_t i = 0; i < order.m_numToys; i++) {
                if (order.m_toys[i] != nullptr) {
                    os << *(order.m_toys[i]);
                }
            }
        }

        printLine(os);
        return os;
    }

} // seneca