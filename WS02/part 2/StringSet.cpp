// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 01/29/2024
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.

#include "StringSet.h"
#include <fstream>
#include <string>

namespace seneca {

    StringSet::StringSet(const char *filename) {
        // Checking for valid filename
        if (filename){
            std::ifstream readFile(filename);
            std::string temp;

            // Checking if file is open
            if(readFile){
                // Counting the number of strings in the file
                while(getline(readFile, temp, ' ')) ++m_stringCounter;

                //reset file
                readFile.clear();
                readFile.seekg(0, std::ios::beg);

                m_strings = new std::string[m_stringCounter];

                int i = 0;
		        while(getline(readFile, m_strings[i], ' '))++i;
            }
        }
    }

    StringSet::StringSet(const StringSet &src) {
        // Copy constructor
        *this = src;
    }

    StringSet &StringSet::operator=(const StringSet &src) {
        // Copy assignment operator
        if(this != &src){
            // Checking if the current object has any strings
            if(this->m_strings){
                delete[] m_strings;
                m_strings = {};
            }

            // Copying from src to current object
            this->m_stringCounter = src.m_stringCounter;
            this->m_strings = new std::string[m_stringCounter];

            for(size_t i = 0 ; i < m_stringCounter; ++i){
                this->m_strings[i] = src.m_strings[i];
            }
        }
        return *this;
    }

    StringSet::StringSet(StringSet &&src) {
        // Move constructor
        *this = std::move(src);
    }

    StringSet &StringSet::operator=(StringSet &&src) {
        // Move assignment operator
        if(this != &src){
            if(this->m_strings){
                delete[] m_strings;
                m_strings = {};
            }
            // Moving from src to current object
            this->m_stringCounter = src.m_stringCounter;
            src.m_stringCounter = {};
            this->m_strings = src.m_strings;
            src.m_strings = {};
        }
        return *this;
    }

    StringSet::~StringSet() {
        // Destructor
        if(m_strings)delete[] m_strings;
    }

    size_t StringSet::size() const {
        return m_stringCounter;
    }

    std::string StringSet::operator[](size_t index) const {
        // Overloaded operator returning the string at the index
        return (index < m_stringCounter) ? m_strings[index] : std::string();
    }
} // seneca