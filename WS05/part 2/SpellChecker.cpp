//
// Created by Tomas Rochwerger on 2024-02-18.
//

#include "SpellChecker.h"
#include <fstream>
#include <iomanip>

namespace seneca {
    SpellChecker::SpellChecker(const char *filename) {
        std::ifstream file(filename);
        if(!file){
            throw "Bad file name!";
        }
        std::string line;
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
        while(std::getline(file, line) && i < 6){
            m_badWords[i] = line.substr(0, line.find(' '));
            m_badWords[i] = trim(m_badWords[i]);
            m_goodWords[i] = line.substr(line.find(' ')+1);
            m_goodWords[i] = trim(m_goodWords[i]);
            i++;
        }
    }

    void SpellChecker::operator()(std::string &text) {
        for(int i = 0; i < 6; i++){
            while(text.find(m_badWords[i]) != std::string::npos){
                text.replace(text.find(m_badWords[i]), m_badWords[i].length(), m_goodWords[i]);
                m_badWordsCount[i]++;

            }
        }
    }

    void SpellChecker::showStatistics(std::ostream &out) const {
        //void showStatistics(std::ostream& out) const: inserts into the parameter how many times each misspelled word has been replaced by the correct word using the current instance. The format of the output is:
        //
        //BAD_WORD: CNT replacements<endl>
        //
        //where BAD_WORD is to be printed on a field of size 15, aligned to the right.
        out << "Spellchecker Statistics" << std::endl;
        for(int i = 0; i < 6; i++){
            out << std::setw(15) << std::right << m_badWords[i] << ": " << m_badWordsCount[i]  << " replacements" << std::endl;
        }

    }
} // seneca