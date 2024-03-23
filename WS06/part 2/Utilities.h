// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 03/10/2024
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include "Person.h"
#include <istream>

namespace seneca {

    Person* buildInstance(std::istream& in);
    std::string trim(std::string& str);
}

#endif //SENECA_UTILITIES_H
