// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 03/10/2024
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SENECA_STUDENT_H
#define SENECA_STUDENT_H
#include "Person.h"

namespace seneca {

    class Student : public Person{
        std::string m_name;
        std::string m_age;
        std::string m_id;
        std::string* m_courses;
        size_t m_count{};
    public:
        Student(std::istream& in);
        void display(std::ostream& out) const override;

        std::string status() const override{
            return "Student";
        };
        std::string name() const override{
            return m_name;
        };
        std::string age() const override{
            return m_age;
        };
        std::string id() const override{
            return m_id;
        };

        Student(const Student&) = delete;
        Student& operator=(const Student&) = delete;

        ~Student() override{
            delete[] m_courses;
        }
    };
}

#endif //SENECA_STUDENT_H
