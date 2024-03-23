//
// Created by Tomas Rochwerger on 2024-02-18.
//

#include "Book.h"
#include <sstream>
#include <iomanip>
namespace seneca {

    Book::Book(const std::string &strBook) {
        std::istringstream is(strBook);
        std::string token;
        int i = 0;
        auto trim = [](std::string &str) {
            // find the first non-space character
            size_t start = str.find_first_not_of(" \t");
            // find the last non-space character
            size_t end = str.find_last_not_of(" \t");
            // No non-space characters
            if(start == std::string::npos || end == std::string::npos)
                return std::string("");
            return str.substr(start, end - start + 1);
        };
        while (i < 5 && std::getline(is, token, ',')) {
            if (i == 0) {
                m_author = trim(token);
            } else if (i == 1) {
                m_title = trim(token);
            } else if (i == 2) {
                m_country = trim(token);
            } else if (i == 3) {
                m_price = std::stod(token);
            } else if (i == 4) {
                m_yearPublished = std::stoi(token);
            }
            ++i;
        }
        if (i == 5) {
            std::getline(is, token); // read the rest of the line into the description
            m_desc = trim(token);
        }
    }

    const std::string &Book::title() const {
        return m_title;
    }

    const std::string &Book::country() const {
        return m_country;
    }

    const size_t &Book::year() const {
        return m_yearPublished;
    }

    double &Book::price() {
        return m_price;
    }

    template <typename T>
    void outputWithWidth(std::ostream &os, int width , T value, char endLine = '|') {
        char space = ' ';
        os << space;
        os.setf(std::ios::right);
        os.width(width);
        os.fill(space);
        //if T value is a double, set precision to 2
        if (std::is_same<T, double>::value) {
            os << std::fixed << std::setprecision(2) << value << space << endLine ;
        } else{
            os << value << space << endLine ;
        }
//        os.unsetf(std::ios::right); // clear the formatting
    }

    std::ostream &operator<<(std::ostream &os, const Book &book) {
        outputWithWidth(os, 19, book.m_author);
        outputWithWidth(os, 22, book.m_title);
        outputWithWidth(os, 5, book.m_country);
        outputWithWidth(os, 4, book.m_yearPublished);
        outputWithWidth(os, 6, book.m_price);
        os << ' ' << book.m_desc << std::endl;
        return os;
    }
} // seneca