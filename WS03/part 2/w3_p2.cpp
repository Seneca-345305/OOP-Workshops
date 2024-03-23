// Name: Tomas Rochwerger
// Student Number: 159432210
// Seneca Email: trochwerger@myseneca.ca
// Date of Completion: 02/04/2024
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include <iostream>
#include <iomanip>
#include "Set.h"
#include "Collection.h"
#include "Pair.h"

int cout = 0; // won't compile if headers don't follow convention

int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; i++)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";

	// Data to be used by the template classes
	long   iData[]{    16,    12,     9,      3,    21,    12, 23 };
	double dData[]{ 1.222, 5.777, 1.223, 51.333, 8.888, 1.221 };
	seneca::Pair pData[]{
		seneca::Pair("static memory", "memory allocated during the compilation time"),
		seneca::Pair("programmer", "a person who writes code"),
		seneca::Pair("dynamic memory", "memory allocated during the runtime"),
		seneca::Pair("client of a class", "a piece of code that uses the class"),
		seneca::Pair("dynamic memory", "memory allocated with 'new' operator"),
		seneca::Pair("user", "a person who runs and interracts with the program"),
		seneca::Pair("array", "a contiguous block of memory storing multiple objects"),
		seneca::Pair("client of a function", "a piece of code that uses the function"),
		seneca::Pair("user", "Just John!"),
	};

	{
		std::cout << "******************************************************\n";
		std::cout << "* Testing the Collection of Integers                 *\n";
		std::cout << "******************************************************\n";
		seneca::Collection<long, 20> colIntegers;

		for (const auto& item : iData)
			colIntegers.add(item);

		std::cout << "Collection size: [" << colIntegers.size() << "]\n";
		colIntegers.display();

		std::cout << "Item [0]: " << colIntegers[0] << "\n";
		std::cout << "Item [5]: " << colIntegers[5] << "\n";
		std::cout << "Item [9]: " << colIntegers[9] << "\n";
		std::cout << "******************************************************\n\n";
	}

	{
		std::cout << "******************************************************\n";
		std::cout << "* Testing the Set of Integers                        *\n";
		std::cout << "******************************************************\n";
		seneca::Collection<long, 100>* setIntegers = new seneca::Set<long>();

		for (const auto& item : iData)
			setIntegers->add(item);

		std::cout << "Set size: [" << setIntegers->size() << "]\n";
		setIntegers->display();

		std::cout << "Item [0]: " << (*setIntegers)[0] << "\n";
		std::cout << "Item [5]: " << (*setIntegers)[5] << "\n";
		std::cout << "Item [9]: " << (*setIntegers)[9] << "\n";
		std::cout << "******************************************************\n\n";
		delete setIntegers;
	}

	{
		std::cout << "******************************************************\n";
		std::cout << "* Testing the Collection of Floats                   *\n";
		std::cout << "******************************************************\n";
		seneca::Collection<double, 30> colFloats;

		for (const auto& item : dData)
			colFloats.add(item);

		std::cout << "Collection size: [" << colFloats.size() << "]\n";
		colFloats.display();

		std::cout << "Item [0]: " << colFloats[0] << "\n";
		std::cout << "Item [5]: " << colFloats[5] << "\n";
		std::cout << "Item [9]: " << colFloats[9] << "\n";
		std::cout << "******************************************************\n\n";
	}

	{
		std::cout << "******************************************************\n";
		std::cout << "* Testing the Set of Floats                          *\n";
		std::cout << "******************************************************\n";
		seneca::Collection<double, 100>* setFloats = new seneca::Set<double>;

		for (const auto& item : dData)
			setFloats->add(item);
		
		std::cout << "Set size: [" << setFloats->size() << "]\n";
		setFloats->display();

		std::cout << "Item [0]: " << (*setFloats)[0] << "\n";
		std::cout << "Item [5]: " << (*setFloats)[5] << "\n";
		std::cout << "Item [9]: " << (*setFloats)[9] << "\n";
		std::cout << "******************************************************\n\n";
		delete setFloats;
	}

	{
		std::cout << "******************************************************\n";
		std::cout << "* Testing the Collection of Pairs                    *\n";
		std::cout << "******************************************************\n";
		seneca::Collection<seneca::Pair, 50> colDictionary;

		for (const auto& item : pData)
			colDictionary.add(item);

		std::cout << "Collection size: [" << colDictionary.size() << "]\n";
		colDictionary.display();

		std::cout << "Item [0]: [" << colDictionary[0].getKey()   << "]["
		                           << colDictionary[0].getValue() << "]\n";
		std::cout << "Item [8]: [" << colDictionary[8].getKey()   << "]["
		                           << colDictionary[8].getValue() << "]\n";
		std::cout << "Item [9]: [" << colDictionary[9].getKey()   << "]["
		                           << colDictionary[9].getValue() << "]\n";
		std::cout << "******************************************************\n\n";
	}

	{
		std::cout << "******************************************************\n";
		std::cout << "* Testing the Set of Pairs                           *\n";
		std::cout << "******************************************************\n";
		seneca::Collection<seneca::Pair, 100>* setDictionary = new seneca::Set<seneca::Pair>();

		for (const auto& item : pData)
			setDictionary->add(item);

		std::cout << "Set size: [" << setDictionary->size() << "]\n";
		setDictionary->display();

		std::cout << "Item [1]: ["  << (*setDictionary)[1].getKey()    << "]["
		                            << (*setDictionary)[1].getValue()  << "]\n";
		std::cout << "Item [4]: ["  << (*setDictionary)[4].getKey()    << "]["
		                            << (*setDictionary)[4].getValue()  << "]\n";
		std::cout << "Item [11]: [" << (*setDictionary)[11].getKey()   << "]["
		                            << (*setDictionary)[11].getValue() << "]\n";
		std::cout << "******************************************************\n\n";
		delete setDictionary;
	}

	return cout;
}
