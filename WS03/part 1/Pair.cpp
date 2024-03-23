//
// Created by Tomas Rochwerger on 2024-01-31.
//
#include <iostream>
#include <iomanip>
#include "Pair.h"


namespace seneca {

    // Implement the missing functions
    bool Pair::operator==(const Pair& other) const {
        return m_key == other.m_key;
    }

    // Displaying the pair
    std::ostream& Pair::display(std::ostream& os) const {
        return os <<  std::right << std::setw(20) << m_key << ": " << std::left << m_value;
    }

    // Overloading the << operator to output pair
    std::ostream &operator<<(std::ostream &os, const Pair &pair) {
        return pair.display(os);
    }

} // namespace seneca
