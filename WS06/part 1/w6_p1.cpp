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
        std::cerr << "ERROR: Cannot open file [" << filename << "].\n";
        return;
    }
    seneca::Person* thePerson = nullptr;
    while(file) {
        try {
            thePerson = seneca::buildInstance(file);
            if (thePerson)
                theCollege += thePerson;
        }
        catch (const std::string &e) {
            std::cout << e << '\n';
        }
    }
}


int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; ++i)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";

	seneca::College theCollege;
	::loadData(argv[1], theCollege);
	theCollege.display(std::cout);

	return cout;
}
