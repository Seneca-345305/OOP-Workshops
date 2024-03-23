// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 2024-02-09
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SENECA_TOY_H
#define SENECA_TOY_H
#include <iostream>


namespace seneca {
    constexpr static float tax = 0.13;
    class Toy {
        size_t m_orderId{};
        std::string m_name{};
        unsigned m_numItems{};
        float m_price{};
    public:
        //Default Constructor
        Toy() = default;

        // Update the number of items, assuming number is correct and does not need to be validated
        void update(int numItems);

        // Extracts the information about the toy from the string and stores tokens in the instances attributes
        // Constructor with one parameter
        explicit Toy(const std::string& toy);

        // Display the toy
        void display(std::ostream &os) const;

        // Friend function to overload the << operator
        friend std::ostream &operator<<(std::ostream &os, const Toy &toy);
    };

    // Helper function to print a line
    std::ostream &printLine(std::ostream &os, int width = 26, char fill = '-');
} // seneca

#endif //SENECA_TOY_H
