//
// Created by Tomas  on 2024-03-07.
//

#include "Utilities.h"

namespace seneca {
    Person* buildInstance(std::istream& in) {
        char ch = '\0';
        in >> ch;
        in.putback(ch);

        if (ch == 'e' || ch == 'E') {
            return new Employee(in);
        }
        else {
            // If the tag is not 'e' or 'E', read the rest of the line and ignore it
            std::string ignoredLine;
            std::getline(in, ignoredLine);
        }

        return nullptr;
    }
} // seneca