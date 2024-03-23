//
// Created by Tomas Rochwerger on 2024-02-18.
//

#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H
#include <iostream>
#include <string>


namespace seneca {

    class Book {
        std::string m_author{};
        std::string m_title{};
        std::string m_country{};
        size_t m_yearPublished{};
        double m_price{};
        std::string m_desc{};
    public:
        // default constructor
        Book() = default;

        // constructor that receives a string with the book information
        Book(const std::string& strBook);

        // Query returning the title of the book
        const std::string& title() const;

        // Query returning the country of the book
        const std::string& country() const;

        // Query returning the year of the book
        const size_t& year() const;

        // Query returning the price of the book by reference allowing the price to be modified
        double& price();

        // Overload the insertion operator to insert the book into an ostream object
        friend std::ostream& operator<<(std::ostream& os, const Book& book);
    };

} // seneca

#endif //SENECA_BOOK_H
