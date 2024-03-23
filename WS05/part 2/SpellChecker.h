//
// Created by Tomas Rochwerger on 2024-02-18.
//

#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H
#include <string>
namespace seneca {

    class SpellChecker {
        std::string m_badWords[6];
        std::string m_goodWords[6];
        int m_badWordsCount[6]{};

    public:
        SpellChecker(const char* filename);
        void operator()(std::string& text);
        void showStatistics(std::ostream& out) const;
    };

} // seneca

#endif //SENECA_SPELLCHECKER_H
