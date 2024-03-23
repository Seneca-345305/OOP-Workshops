//
// Created by Tomas  on 2024-03-07.
//
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
} // seneca

#endif //SENECA_EMPLOYEE_H
