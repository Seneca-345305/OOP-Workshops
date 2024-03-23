//
// Created by Tomas Rochwerger on 2024-01-23.
//

#ifndef SENECA_STRINGSET_H
#define SENECA_STRINGSET_H
#include <string>

namespace seneca {

    class StringSet {
        size_t m_stringCounter{};
        std::string* m_strings{};
    public:
        StringSet(){};
        StringSet(const char* filename);
        StringSet(const StringSet& src);
        StringSet& operator=(const StringSet& src);
        StringSet(StringSet&& src);
        StringSet& operator=(StringSet&& src);
        ~StringSet();
        size_t size() const;
        std::string operator[](size_t index) const;
    };

} // seneca

#endif //SENECA_STRINGSET_H
