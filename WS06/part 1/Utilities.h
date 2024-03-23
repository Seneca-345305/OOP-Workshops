//
// Created by Tomas  on 2024-03-07.
//

#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include "Employee.h"
#include <istream>

namespace seneca {

    Person* buildInstance(std::istream& in);
} // namespace seneca

#endif //SENECA_UTILITIES_H
