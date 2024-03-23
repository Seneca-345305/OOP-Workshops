//
// Created by Tomas Rochwerger on 2024-02-18.
//

#include "Movie.h"
#include <sstream>

namespace seneca {
    const std::string &Movie::title() const {
        return m_title;
    }

    Movie::Movie(const std::string &strMovie) {
        std::istringstream is(strMovie);
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
        while(i<2 && std::getline(is, token, ',')){
            if(i == 0){
                m_title = trim(token);
            } else if(i == 1){
                m_year = std::stoi(token);
            }
            ++i;
        }
        if(i == 2){
            std::getline(is, token); // read the rest of the line into the description
            m_desc = trim(token);
        }

    }

    template <typename T>
    void outputWithWidth(std::ostream &os, int width , T value, char endLine = '|') {
        char space = ' ';
        os << space;
        os.setf(std::ios::right);
        os.width(width);
        os.fill(space);
        os << value << space << endLine ;
//        os.unsetf(std::ios::right); // clear the formatting
    }

    std::ostream &operator<<(std::ostream &os, const Movie &movie) {
        outputWithWidth(os, 39, movie.title());
        outputWithWidth(os, 4, movie.m_year);
        os <<' ' << movie.m_desc << std::endl;
        return os;
    }


} // seneca