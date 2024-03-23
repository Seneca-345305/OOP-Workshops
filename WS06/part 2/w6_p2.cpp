// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 03/10/2024
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Utilities.h"
#include "Utilities.h"
#include "College.h"
#include "College.h"

int cout = 0; // won't compile if headers don't follow convention regarding namespaces

void loadData(const char* filename, seneca::College& theCollege)
{
	std::ifstream file(filename);
	if (!file)
	{
		std::cout << "ERROR: Cannot open file [" << filename << "].\n";
		return;
	}
	seneca::Person* thePerson = nullptr;
	while (file) {
        // TODO: This code can throw errors to signal that something
        //         went wrong while extracting data. Write code to catch
        //         and handle the exceptions:
        try {
            thePerson = seneca::buildInstance(file);
            if (thePerson)
                theCollege += thePerson;
        }
        catch (const std::string &err) {
            std::cout << err << std::endl;
        }
        catch (...) {
            std::cout << "Unknown error!" << std::endl;
        }
    }
}


int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; i++)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";

	seneca::College theCollege;
	::loadData(argv[1], theCollege);
	theCollege.display(std::cout);

	std::list<const seneca::Person*> persons;
	{
		// TODO: Create a lambda expression that receives as parameter `const seneca::Person*`
		//         and returns true if the person is student.
		auto students = [](const seneca::Person* person) {
            return person->status() == "Student";
        };
		theCollege.select(students, persons);
	
		std::cout << "|                                        Test #3 Students in the college!                                              |\n";
		std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
		for (auto it = persons.begin(); it != persons.end(); ++it)
		{
			(*it)->display(std::cout);
			std::cout << std::endl;
		}
		std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
	}

	persons.clear();
	{
		// TODO: Create a lambda expression that receives as parameter `const seneca::Person*`
		//         and returns true if the person is professor.
		auto professors = [](const seneca::Person* person) {
            return person->status() == "Professor";
        };
		theCollege.select(professors, persons);
	
		std::cout << "|                                        Test #4 Professors in the college!                                            |\n";
		std::cout << "------------------------------------------------------------------------------------------------------------------------\n";		
		for (const auto person : persons)
		{
			person->display(std::cout);
			std::cout << std::endl;
		}
		std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
	}

	return cout;
}
