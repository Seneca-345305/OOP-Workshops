//
// Created by Tomas Rochwerger on 2024-02-09.
//

#include "Toy.h"
#include <string>
#include <iomanip>
#include <iostream>

namespace seneca {
    void Toy::update(int numItems) {
        m_numItems = numItems;
    }

    std::string trim(const std::string& str) {
        size_t end = str.find_last_not_of(" \t");
        if(end == std::string::npos) // No non-space characters
            return "";
        return str.substr(0, end + 1);
    }

    Toy::Toy(const std::string &toy) {
        size_t pos = 0;
        std::string token;
        std::string delimiter = ":";
        int i = 0;
        std::string toyCopy = toy; // create a copy of toy
        while ((pos = toyCopy.find(delimiter)) != std::string::npos) {
            token = toyCopy.substr(0, pos);
            if (i == 0) {
                m_orderId = std::stoi(token);
            } else if (i == 1) {
                m_name = trim(token);
            } else if (i == 2) {
                m_numItems = std::stoi(token);
            }
            toyCopy.erase(0, pos + delimiter.length()); // modify the copy
            i++;
        }
        m_price = std::stof(toyCopy); // use std::stof here
    }

    void Toy::display(std::ostream &os) const {
        os << "Toy";
        os.setf(std::ios::right);
        os.width(8);
        os << m_orderId << ":" ;
        os.width(18);
        os << m_name;
        os.width(3);
        os << m_numItems << " items";
        os << std::setw(8) << std::fixed << std::setprecision(2) << m_price << "/item  subtotal:";
        os << std::setw(7) << m_price * m_numItems << " tax:";
        os << std::setw(6) << m_price * m_numItems * tax << " total:";
        os << std::setw(7) << m_price * m_numItems * (1 + tax) << std::endl;
    }

    std::ostream &operator<<(std::ostream &os, const Toy &toy) {
        toy.display(os);
        return os;
    }
} // seneca