//
// Created by Tomas Rochwerger on 2024-01-23.
//

#include "StringSet.h"
#include <fstream>
#include <string>
#include <iostream>

namespace seneca {

    StringSet::StringSet(const char *filename) {
        if (filename){
            std::ifstream readFile(filename);
            std::string temp;

            if(readFile){
                while(getline(readFile, temp, ' ')) ++m_stringCounter;
                m_strings = new std::string[m_stringCounter];
                readFile.clear();
                readFile.seekg(0, std::ios::beg);

                for(int i; i < m_stringCounter; ++i){
                    if(!(getline(readFile, m_strings[i], ' '))){
                        std::cerr << "Error reading file!\n";
                        break;
                    }
                }
            }
        }
    }

    StringSet::StringSet(const StringSet &src) {
        *this = src;
    }

    StringSet &StringSet::operator=(const StringSet &src) {
        if(this != &src){
            if(this->m_strings){
                delete[] m_strings;
                m_strings = {};
            }
            this->m_stringCounter = src.m_stringCounter;
            this->m_strings = new std::string[m_stringCounter];
            for(auto i : *src.m_strings){
                this->m_strings[i] = src.m_strings[i];
            }
        }
        return *this;
    }

    StringSet::StringSet(StringSet &&src) {
        *this = std::move(src);
    }

    StringSet &StringSet::operator=(StringSet &&src) {
        if(this != &src){
            if(this->m_strings){
                delete[] m_strings;
                m_strings = {};
            }
            this->m_stringCounter = src.m_stringCounter;
            src.m_stringCounter = {};
            this->m_strings = src.m_strings;
            src.m_strings = {};
        }
        return *this;
    }

    StringSet::~StringSet() {
        if(m_strings)delete[] m_strings;
    }

    size_t StringSet::size() const {
        return m_stringCounter;
    }

    std::string StringSet::operator[](size_t index) const {
        return (index < m_stringCounter) ? m_strings[index] : std::string();
    }
} // seneca