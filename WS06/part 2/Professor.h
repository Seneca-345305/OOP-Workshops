// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 03/10/2024
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


#ifndef SENECA_PROFESSOR_H
#define SENECA_PROFESSOR_H
#include "Employee.h"

namespace seneca {

    class Professor : public Employee{
        std::string m_department;
    public:
        Professor(std::istream& in);
        void display(std::ostream& out) const override;

        std::string status() const override{
            return "Professor";
        };

        std::string department() const{
            return m_department;
        };
    };
}

#endif //SENECA_PROFESSOR_H
