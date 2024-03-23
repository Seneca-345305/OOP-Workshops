//
// Created by Tomas Rochwerger on 2024-02-18.
//

#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H
#include <iostream>

namespace seneca {
    template <typename T>
    class Collection {
        std::string m_name{};
        T* m_items{};
        size_t m_size{} ;
        void (*m_observer)(const Collection<T>&, const T&) = nullptr;
    public:
          // default constructor
        Collection(const std::string& name) :m_name(name){}
        // destructor
        ~Collection() { delete[] m_items; }

        // Query returning the name of the collection
        const std::string& name() const { return m_name; }

        // Query returning the number of items in the collection
        size_t size() const { return m_size; }

        // set the observer function
        void setObserver(void (*observer)(const Collection<T>&, const T&)) { m_observer = observer; }

        // add an item to the collection
        Collection<T>& operator+=(const T& item) {
            bool found = false;
            for (size_t i = 0; i < m_size; i++) {
                if (m_items[i].title() == item.title()) {
                    found = true;
                }
            }
            if (!found) {
                T* temp = new T[m_size + 1];
                for (size_t i = 0; i < m_size; i++) {
                    temp[i] = m_items[i];
                }
                temp[m_size] = item;
                m_size++;
                delete[] m_items;
                m_items = temp;
                if (m_observer) {
                    m_observer(*this, item);
                }
            }
            return *this;
        }
        T& operator[](size_t idx) const {
            if (idx >= m_size) {
                throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_size) + "] items.");
            }
            return m_items[idx];
        }
        T* operator[](const std::string& title) const {
            for (size_t i = 0; i < m_size; i++) {
                if (m_items[i].title() == title) {
                    return &m_items[i];
                }
            }
            return nullptr;
        }
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Collection<T>& collection) {
        for (size_t i = 0; i < collection.size(); i++) {
            os << collection[i];
        }
        return os;
    }

} // seneca

#endif //SENECA_COLLECTION_H
