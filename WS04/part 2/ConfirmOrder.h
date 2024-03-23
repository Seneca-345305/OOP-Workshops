// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 2024-02-09
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SENECA_CONFIRMORDER_H
#define SENECA_CONFIRMORDER_H
#include "Toy.h"

namespace seneca {

    class ConfirmOrder {
        const seneca::Toy **m_toys{};
        size_t m_numToys{};
    public:
        //Default Constructor
        ConfirmOrder() = default;

        //Copy Constructor
        ConfirmOrder(const ConfirmOrder &src);

        //Move Constructor
        ConfirmOrder(ConfirmOrder &&src) noexcept;

        // Copy assignment operator
        ConfirmOrder &operator=(const ConfirmOrder &src);

        // Move assignment operator
        ConfirmOrder &operator=(ConfirmOrder &&src) noexcept;

        //Destructor
        ~ConfirmOrder();

        // Add a toy to the list of confirmations
        ConfirmOrder &operator+=(const Toy &toy);

        // Remove a toy from the list of confirmations
        ConfirmOrder &operator-=(const Toy &toy);

        // Output operator
        friend std::ostream &operator<<(std::ostream &os, const ConfirmOrder &order);
    };

}// seneca

#endif //SENECA_CONFIRMORDER_H
