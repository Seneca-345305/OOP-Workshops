// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 03/10/2024
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


#include "Utilities.h"
#include "Employee.h"
#include "Student.h"
#include "Professor.h"
#include <string>
#include <iostream>
#include <sstream>

namespace seneca {

    Person* buildInstance(std::istream& in) {
        char ch = '\0';
        std::string line;

        std::getline(in, line);
        std::istringstream iss(line);
        ch = line[0];

        if (ch == 'e' || ch == 'E') {
            return new Employee(iss);
        }
        else if (ch == 's' || ch == 'S') {
            return new Student(iss);
        }
        else if (ch == 'p' || ch == 'P') {
            return new Professor(iss);
        }

        return nullptr;
    }

    std::string trim(std::string &str) {
        // Find the first non-space and non-newline character
        size_t start = str.find_first_not_of(" \t\n");
        // If all characters are spaces or newlines, return an empty string
        if (start == std::string::npos)
            return "";

        // Find the last non-space and non-newline character
        size_t end = str.find_last_not_of(" \t\n");

        // Extract the substring without leading and trailing spaces and newlines
        return str.substr(start, end - start + 1);
    }
}