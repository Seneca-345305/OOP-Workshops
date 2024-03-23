// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 03/10/2024
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "Person.h"
#include <iostream>

#ifndef SENECA_EMPLOYEE_H
#define SENECA_EMPLOYEE_H

namespace seneca {

    class Employee : public Person {
    private:
        std::string m_name;
        int m_age;
        std::string m_id;

    public:
        explicit Employee(std::istream& in);

        std::string status() const override {
            return "Employee";
        }

        std::string name() const override{
            return m_name;
        }

        std::string id() const override{
            return m_id;
        }

        std::string age() const override{
            return std::to_string(m_age);
        }

        void display(std::ostream& out) const override;

        ~Employee() override = default;
    };
}

#endif //SENECA_EMPLOYEE_H
