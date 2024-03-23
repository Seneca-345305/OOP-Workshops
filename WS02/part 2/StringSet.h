// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 01/29/2024
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.

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
