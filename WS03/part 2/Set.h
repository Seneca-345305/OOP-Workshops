// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 02/04/2024
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SENECA_SET_H
#define SENECA_SET_H
#include "Collection.h"
#include <cmath>

namespace seneca {
    template<typename T>
    class Set : public Collection<T, 100> {
    public:

        // overrides the inherited add function to prevent duplicates
        bool add(const T &item) override;

        // Returns true if the item is already in the collection
//        bool containsDouble(const double &item) const{
//            bool found = false;
//            for (size_t i = 0; i < Collection<double, 100>::size(); i++) {
//                if (std::fabs(Collection<double, 100>::operator[](i) - item) <= 0.01) found = true;
//            }
//            return found;
//        };

        // Returns true if the item is already in the collection
        bool contains(const T &item) const{
            bool found = false;
            for (size_t i = 0; i < Collection<T, 100>::size(); i++) {
                if (Collection<T, 100>::operator[](i) == item) found = true;
            }
            return found;
        };

    };

    // Overrides the inherited add function to prevent duplicates
    template<typename T>
    bool Set<T>::add(const T &item) {
        bool added = false;
        if (!Collection<T, 100>::checkSpace()){
            added = false;
        } else if (contains(item)){
            added = false;
        } else {
            Collection<T, 100>::add(item);
            added = true;
        }
            return added;
    }

    // Specialization for double
    // Returns true if the item is already in the collection, specialized for double
    template<>
    bool Set<double>::contains(const double &item) const {
        bool found = false;
        for (size_t i = 0; i < Collection<double, 100>::size(); i++) {
            if (std::fabs(Collection<double, 100>::operator[](i) - item) <= 0.01) found = true;
        }
        return found;
    }

    // Overrides the inherited add function to prevent duplicates, specialized for double
    template<>
    bool Set<double>::add(const double &item) {
        bool added = false;
        if (!Collection<double, 100>::checkSpace()){
            added = false;
        } else if (contains(item)){
            added = false;
        } else {
            Collection<double, 100>::add(item);
            added = true;
        }
        return added;
    }


} // seneca

#endif //SENECA_SET_H
