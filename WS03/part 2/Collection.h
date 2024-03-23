// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 02/04/2024
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include "Pair.h"

namespace seneca {
    template<typename T, size_t CAPACITY>
    class Collection {
    private:
        T m_elements[CAPACITY];
        size_t m_size{};
        static T m_dummy; // Dummy object
    public:
        // Returns the number of elements in the collection
        size_t size() const;

        // Displays the collection
        std::ostream &display(std::ostream &os = std::cout) const;

        // Check for space
        bool checkSpace() const;

        // Adds a copy of item to the collection if there is space
        virtual bool add(const T &item);

        // Returns a reference to the element at index of the collection
        T operator[](size_t index) const;

        // Virtual destructor
        virtual ~Collection() = default;
    };

    // Initialization of dummy object
    template<typename T, size_t CAPACITY>
    T Collection<T, CAPACITY>::m_dummy{};

    //Specialization for two argument constructor
    template<>
    Pair Collection<Pair, 100>::m_dummy{"No Key", "No Value"};

    // Getting size of collection
    template<typename T, size_t CAPACITY>
    size_t Collection<T, CAPACITY>::size() const{
        return m_size;
    }

    // Displaying collection
    template<typename T, size_t CAPACITY>
    std::ostream &Collection<T, CAPACITY>::display(std::ostream &os) const{
         std::string line = "----------------------\n";
         std::string title = "| Collection Content |\n";
            os << line << title << line;
        for (size_t i = 0; i < m_size; i++)
            os << m_elements[i] << std::endl;
        os << line;
        return os;
    }

    //checking for capicity
    template<typename T, size_t CAPACITY>
    bool Collection<T, CAPACITY>::checkSpace() const{
        return m_size < CAPACITY;
    }

    // Adding item to collection
    template<typename T, size_t CAPACITY>
    bool Collection<T, CAPACITY>::add(const T &item){
        bool added = false;
        if (checkSpace()){
            m_elements[m_size] = item;
            ++m_size;
            added = true;
        }
        return added;
    }

    // Overloading [] operator to return element at index
    template<typename T, size_t CAPACITY>
    T Collection<T, CAPACITY>::operator[](size_t index) const{
        return (index < m_size) ? m_elements[index] : m_dummy;
    }

};
#endif // SENECA_COLLECTION_H
