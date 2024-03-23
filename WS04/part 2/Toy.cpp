// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 2024-02-09
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "Toy.h"

#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace seneca {

    Toy::Toy(const std::string &toy) {

        // create a stream from the string
        std::istringstream is(toy);
        std::string token;
        int i = 0;
        while (std::getline(is, token, ':')) {
            //Get the first token (id)
            if (i == 0) {
                m_orderId = std::stoi(token);
            } else if (i == 1) {
                // lambda function to remove leading and trailing spaces
                auto trim = [](std::string &str) {
                    // find the last non-space character
                    size_t end = str.find_last_not_of(" \t");
                    // No non-space characters
                    if(end == std::string::npos)
                        return std::string("");
                    return str.substr(0, end + 1);
                };
                m_name = trim(token);
            } else if (i == 2) {
                m_numItems = std::stoi(token);
            } else if (i == 3) {
                m_price = std::stof(token);
            }
            ++i;
        }
    }

    // Helper function to output a value with a specific width
    template <typename T>
    void outputWithWidth(std::ostream &os, int width, T value) {
        os.setf(std::ios::right);
        os.width(width);
        os << value;
    }

    // Display the toy
    void Toy::display(std::ostream &os) const {
        os << "Toy";
        outputWithWidth(os, 8, m_orderId);
        os << ":";
        outputWithWidth(os, 18, m_name);
        outputWithWidth(os, 3, m_numItems);
        os << " items";
        os << std::fixed << std::setprecision(2);
        outputWithWidth(os, 8, m_price);
        os << "/item  subtotal:";
        outputWithWidth(os, 7, m_price * m_numItems);
        os << " tax:";
        outputWithWidth(os, 6, m_price * m_numItems * tax);
        os << " total:";
        outputWithWidth(os, 7, m_price * m_numItems * (1 + tax));
        os << std::endl;
    }

    // Update the number of items, assuming number is correct and does not need to be validated
    void Toy::update(int numItems) {
        m_numItems = numItems;
    }

    std::ostream &operator<<(std::ostream &os, const Toy &toy) {
        toy.display(os);
        return os;
    }

    std::ostream &printLine(std::ostream &os, int width, char fill) {
        std::string line(width, fill);
        line += '\n';
        os << line;
        return os;
    }

} // seneca