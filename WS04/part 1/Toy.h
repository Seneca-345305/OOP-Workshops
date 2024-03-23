//
// Created by Tomas Rochwerger on 2024-02-09.
//

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

        std::string trim(const std::string& str);

        //Constructor
        Toy(const std::string& toy);

        //Display the toy
        void display(std::ostream &os) const;

        friend std::ostream &operator<<(std::ostream &os, const Toy &toy);
    };



} // seneca

#endif //SENECA_TOY_H
