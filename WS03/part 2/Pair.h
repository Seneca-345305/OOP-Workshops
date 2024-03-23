// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 02/04/2024
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SENECA_PAIR_H
#define SENECA_PAIR_H

#include <string>

namespace seneca {

    class Pair {
        std::string m_key{};
        std::string m_value{};

    public:
        const std::string& getKey() const { return m_key; }
        const std::string& getValue() const { return m_value; }
        Pair(const std::string& key, const std::string& value) : m_key{key}, m_value{value} {};
        Pair() = default;
        // Add the missing prototypes
        bool operator==(const Pair& other) const;
        std::ostream& display(std::ostream& os) const;
    };
    std::ostream &operator<<(std::ostream &os, const Pair &pair);

} // namespace seneca

#endif // SENECA_PAIR_H
