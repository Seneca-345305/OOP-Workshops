#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Station.h"
#include "Station.h"           // intentional
#include "Workstation.h"
#include "Workstation.h"       // intentional
#include "CustomerOrder.h"
#include "CustomerOrder.h"     // intentional
#include "Utilities.h"
#include "Utilities.h"         // intentional
#include "LineManager.h"
#include "LineManager.h"       // intentional

// Cheching if header guards exist and follow convention.
#ifndef SENECA_STATION_H
    #error "The header guard for 'Station.h' doesn't follow the convention!"
#endif
#ifndef SENECA_UTILITIES_H
    #error "The header guard for 'Utilities.h' doesn't follow the convention!"
#endif
#ifndef SENECA_CUSTOMERORDER_H
    #error "The header guard for 'CustomerOrder.h' doesn't follow the convention!"
#endif
#ifndef SENECA_WORKSTATION_H
    #error "The header guard for 'Workstation.h' doesn't follow the convention!"
#endif
#ifndef SENECA_LINEMANAGER_H
    #error "The header guard for 'LineManager.h' doesn't follow the convention!"
#endif

int cout = 0; // won't compile if headers don't follow convention regarding namespaces

template<typename T>
static void loadFromFile(const char*, std::vector<T>&);
template<typename T>
static void loadFromFile(const char*, std::vector<T*>&);

int main(int argc, char** argv)
{
	std::cout << "Command Line: " << argv[0];
	for (int i = 1; i < argc; ++i)
		std::cout << " " << argv[i];
	std::cout << std::endl << std::endl;
	if (argc != 5) {
		std::cerr << "ERROR: Incorrect number of arguments\n";
		std::exit(1);
	}

	std::vector<seneca::Workstation*> theStations;
	std::vector<seneca::CustomerOrder> theOrders;

	try {
		seneca::Utilities::setDelimiter(',');
		::loadFromFile(argv[1], theStations);
		seneca::Utilities::setDelimiter('|');
		::loadFromFile(argv[2], theStations);

		std::cout << "========================================" << std::endl;
		std::cout << "=         Stations (summary)           =" << std::endl;
		std::cout << "========================================" << std::endl;
		for (const auto* station : theStations)
			station->Station::display(std::cout, false);
		std::cout << std::endl << std::endl;

		std::cout << "========================================" << std::endl;
		std::cout << "=          Stations (full)             =" << std::endl;
		std::cout << "========================================" << std::endl;
		for (const auto* station : theStations)
			station->Station::display(std::cout, true);
		std::cout << std::endl << std::endl;

		//Select an object and verify all the functionality it working
		std::cout << "========================================" << std::endl;
		std::cout << "=          Manual Validation           =" << std::endl;
		std::cout << "========================================" << std::endl;
		std::cout << "getItemName(): " << theStations[0]->getItemName() << std::endl;
		std::cout << "getNextSerialNumber(): " << theStations[0]->getNextSerialNumber() << std::endl;
		std::cout << "getNextSerialNumber(): " << theStations[0]->getNextSerialNumber() << std::endl;
		std::cout << "getQuantity(): " << theStations[0]->getQuantity() << std::endl;
		theStations[0]->updateQuantity();
		std::cout << "getQuantity(): " << theStations[0]->getQuantity() << std::endl;
		std::cout << std::endl << std::endl;


		::loadFromFile<seneca::CustomerOrder>(argv[3], theOrders);

		std::cout << "========================================" << std::endl;
		std::cout << "=                Orders                =" << std::endl;
		std::cout << "========================================" << std::endl;
		for (auto& order : theOrders) {
			order.display(std::cout);
			seneca::g_pending.push_back(std::move(order));
		}
		std::cout << std::endl << std::endl;

		std::cout << "========================================" << std::endl;
		std::cout << "=       Display Stations (loaded)      =" << std::endl;
		std::cout << "========================================" << std::endl;
		seneca::LineManager lm(argv[4], theStations);
		lm.display(std::cout);
		std::cout << std::endl << std::endl;

		std::cout << "========================================" << std::endl;
		std::cout << "=      Display Stations (ordered)      =" << std::endl;
		std::cout << "========================================" << std::endl;
		lm.reorderStations();
		lm.display(std::cout);
		std::cout << std::endl << std::endl;

		std::cout << "========================================" << std::endl;
		std::cout << "=           Filling Orders             =" << std::endl;
		std::cout << "========================================" << std::endl;
		//run the assembly line until all orders processed
		while (!lm.run(std::cout));
		std::cout << std::endl << std::endl;
	}
	catch (const std::string& msg) {
		std::cerr << msg << '\n';
		std::exit(2);
	}

	std::cout << "========================================" << std::endl;
	std::cout << "=      Processed Orders (complete)     =" << std::endl;
	std::cout << "========================================" << std::endl;
	for (const auto& o : seneca::g_completed)
		o.display(std::cout);
	std::cout << std::endl << std::endl;

	std::cout << "========================================" << std::endl;
	std::cout << "=     Processed Orders (incomplete)    =" << std::endl;
	std::cout << "========================================" << std::endl;
	for (const auto& o : seneca::g_incomplete)
		o.display(std::cout);
	std::cout << std::endl << std::endl;

	std::cout << "========================================" << std::endl;
	std::cout << "=          Inventory (full)            =" << std::endl;
	std::cout << "========================================" << std::endl;
	for (const seneca::Station* theItem : theStations)
		theItem->display(std::cout, true);
	std::cout << std::endl;

	// cleanup
	for (auto station : theStations)
		delete station;

	return cout;
}

template<typename T>
static void loadFromFile(const char* filename, std::vector<T>& theCollection)
{
	if (!filename) {
		throw std::string("ERROR: No filename provided.");
	}
	std::ifstream file(filename);
	if (!file)
		throw std::string("Unable to open [") + filename + "] file.";

	std::string record;
	while (!file.eof())
	{
		std::getline(file, record);
		T elem(record);
		theCollection.push_back(std::move(elem));
	}

	file.close();
}

template<typename T>
static void loadFromFile(const char* filename, std::vector<T*>& theCollection)
{
	if (!filename) {
		throw std::string("ERROR: No filename provided.");
	}
	std::ifstream file(filename);
	if (!file)
		throw std::string("Unable to open [") + filename + "] file.";

	std::string record;
	while (!file.eof())
	{
		std::getline(file, record);
		theCollection.push_back(new T(record));
	}

	file.close();
}
