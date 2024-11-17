#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Station.h"
#include "Station.h"        // intentional
#include "Utilities.h"
#include "Utilities.h"      // intentional

// Cheching if header guards exist and follow convention.
#ifndef SENECA_STATION_H
    #error "The header guard for 'Station.h' doesn't follow the convention!"
#endif
#ifndef SENECA_UTILITIES_H
    #error "The header guard for 'Utilities.h' doesn't follow the convention!"
#endif

int cout = 0; // won't compile if headers don't follow convention regarding namespaces

static void loadStations(const char*, std::vector<seneca::Station>&);

int main(int argc, char** argv)
{
	std::cout << "Command Line: " << argv[0];
	for (int i = 1; i < argc; ++i)
		std::cout << " " << argv[i];
	std::cout << std::endl << std::endl;
	if (argc < 3) {
		std::cerr << "ERROR: Insufficient number of arguments\n";
		std::exit(1);
	}

	//**************//
	std::vector<seneca::Station> theStations;
	try
	{
		seneca::Utilities::setDelimiter(',');
		::loadStations(argv[1], theStations);
		seneca::Utilities::setDelimiter('|');
		::loadStations(argv[2], theStations);
	}
	catch (const std::string& err)
	{
		std::cerr << err << '\n';
		std::exit(2);
	}

	std::cout << "========================================" << std::endl;
	std::cout << "=         Stations (summary)           =" << std::endl;
	std::cout << "========================================" << std::endl;
	for (const auto& theItem : theStations)
		theItem.display(std::cout, false);
	std::cout << std::endl << std::endl;

	std::cout << "========================================" << std::endl;
	std::cout << "=          Stations (full)             =" << std::endl;
	std::cout << "========================================" << std::endl;
	for (const auto& theItem : theStations)
		theItem.display(std::cout, true);
	std::cout << std::endl << std::endl;

	//Select an object and verify all the functionality it working
	std::cout << "========================================" << std::endl;
	std::cout << "=          Manual Validation           =" << std::endl;
	std::cout << "========================================" << std::endl;
	std::cout << "getItemName(): " << theStations[0].getItemName() << std::endl;
	std::cout << "getNextSerialNumber(): " << theStations[0].getNextSerialNumber() << std::endl;
	std::cout << "getNextSerialNumber(): " << theStations[0].getNextSerialNumber() << std::endl;
	std::cout << "getQuantity(): " << theStations[0].getQuantity() << std::endl;
	theStations[0].updateQuantity();
	std::cout << "getQuantity(): " << theStations[0].getQuantity() << std::endl;
	std::cout << std::endl;


	std::cout << "========================================" << std::endl;
	std::cout << "=              Utilities               =" << std::endl;
	std::cout << "========================================" << std::endl;
	// create & initialize an array of input data
	const struct { char delim; std::string data; } input[]
	{
		{ 'a', "a"},
		{ 'b', "a" },
		{ 'l', "Hello"},
		{ ',', "apple,orange,banana,kiwi,strawberry,yellow watermellon" },
		{ '|', "Gengar|Arcanine|Bulbasaur|Blaziken|C h a r i z a r d|Umbreon|Lucario|Eevee"}
	};

	for (const auto& item : input)
	{
		seneca::Utilities::setDelimiter(item.delim);
		seneca::Utilities util;
		bool more = true; // if there are more tokens in the input string
		size_t pos = 0u; // position of the next token in the input string
		std::cout << "Data: [" << item.data << "]    Delimiter: [" << item.delim << "]\n";
		while (more)
		{
			try
			{
				auto token = util.extractToken(item.data, pos, more);
				std::cout << "   Token: [" << token << "] [" << util.getFieldWidth() << "]\n";
			}
			catch (...) { std::cout << "   ERROR: No token.\n"; }
		}
	}

	return cout;
}

void loadStations(const char* filenameSt, std::vector<seneca::Station>& theStations)
{
	std::ifstream file(filenameSt);
	if (!file)
		throw std::string("Unable to open [") + filenameSt + "] file";

	// each line from the file represents an item;
	// read one at a time and add it to the inventory
	std::string theRecord;
	while (!file.eof())
	{
		std::getline(file, theRecord);
		seneca::Station newItem(theRecord);
		theStations.push_back(std::move(newItem));
	}
	file.close();
}
