#include <iostream>
#include <iomanip>
#include "dictionary.h"
#include "dictionary.h"      // intentional
#include "settings.h"
#include "settings.h"        // intentional
#include "timeMonitor.h"
#include "timeMonitor.h"     // intentional
#include "logger.h"
#include "logger.h"          // intentional

// Cheching if header guards exist and follow convention.
#ifndef SENECA_DICTIONARY_H
    #error "The header guard for 'dictionary.h' doesn't follow the convention!"
#endif
#ifndef SENECA_SETTINGS_H
    #error "The header guard for 'settings.h' doesn't follow the convention!"
#endif
#ifndef SENECA_TIMEMONITOR_H
    #error "The header guard for 'timeMonitor.h' doesn't follow the convention!"
#endif
#ifndef SENECA_EVENT_H
    #error "The header guard for 'event.h' doesn't follow the convention!"
#endif
#ifndef SENECA_LOGGER_H
    #error "The header guard for 'logger.h' doesn't follow the convention!"
#endif

int cout = 0; // won't compile if headers don't follow convention regarding namespaces

int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "------------------------------------------------------\n";
	for (int i = 0; i < argc; ++i)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "------------------------------------------------------\n\n";

	seneca::Logger log;
	seneca::TimeMonitor timer;

	{
		timer.startEvent("Default Constructor");
		seneca::Dictionary dict;
		log.addEvent(timer.stopEvent());
	}

	timer.startEvent("Custom Constructor");
	seneca::Dictionary dict(argv[1]);
	log.addEvent(timer.stopEvent());

	seneca::g_settings.m_verbose = true;
	seneca::g_settings.m_show_all = true;

	{
		// TEST: Seach functionality
		std::cout << "T1: Search for some words\n";
		std::cout << "==========:==========:==========:==========:==========\n";

		dict.searchWord("Computer");
		std::cout << std::endl;
		dict.searchWord("Zigzag");
		std::cout << std::endl;
		dict.searchWord("Apple");
		std::cout << std::endl;
		dict.searchWord("Germanize");
		std::cout << std::endl;
		dict.searchWord("Passport");
		std::cout << std::endl;
		dict.searchWord("Gone");
		std::cout << std::endl;
		dict.searchWord("Laptop");
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	seneca::g_settings.m_show_all = false;
	seneca::g_settings.m_verbose = false;
	{
		// TEST: Copy Constructor
		std::cout << "T2: Copy Constructor\n";
		std::cout << "==========:==========:==========:==========:==========\n";

		// copy constructor
		timer.startEvent("Copy Constructor");
		seneca::Dictionary dict2 = dict;
		log.addEvent(timer.stopEvent());

		dict.searchWord("Apple");
		dict2.searchWord("Ywis");
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		// TEST: Copy Assignment Operator
		std::cout << "T3: Copy Assignment Operator\n";
		std::cout << "==========:==========:==========:==========:==========\n";

		{
			// check for self assignment
			seneca::Dictionary& alias = dict;
			dict = alias; // crash here if copy assignment is incorrectly implemented
		}

		seneca::Dictionary dict2(argv[2]);
		dict2.searchWord("Efficience");

		timer.startEvent("Copy Assignment Operator");
		dict2 = dict;
		log.addEvent(timer.stopEvent());

		dict.searchWord("Apple");
		dict2.searchWord("Ywis");
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		// TEST: Move Constructor
		std::cout << "T4: Move Constructor\n";
		std::cout << "==========:==========:==========:==========:==========\n";

		seneca::Dictionary dict1 = dict; // make a copy of the bif dictionary
		
		timer.startEvent("Move Constructor");
		seneca::Dictionary dict2 = std::move(dict1);
		log.addEvent(timer.stopEvent());

		dict1.searchWord("Apple");
		dict2.searchWord("Ywis");
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		// TEST: Move Assignment Operator
		std::cout << "T5: Move Assignment Operator\n";
		std::cout << "==========:==========:==========:==========:==========\n";

		{
			// check for self assignment
			seneca::Dictionary& alias = dict;
			dict = std::move(alias); // crash here if move assignment is incorrectly implemented
		}

		seneca::Dictionary dict1(dict);
		seneca::Dictionary dict2(argv[2]);
		dict2.searchWord("Efficience");

		timer.startEvent("Move Assignment Operator");
		dict2 = std::move(dict1);
		log.addEvent(timer.stopEvent());

		dict1.searchWord("Apple");
		dict2.searchWord("Ywis");
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

		// `dict1` and `dict2` will go out of scope. `dict1` is empty and the
		// destructor should be fast, but `dict2` should have the full dictionary
		// and the destructor should be slow(er). We measure the time here.
		timer.startEvent("Destructor");
	}
	log.addEvent(timer.stopEvent());

	{
		// TEST: Search time measurements
		std::cout << "T6: Search Time Measurements\n";
		std::cout << "==========:==========:==========:==========:==========\n";

		seneca::g_settings.m_show_all = false;
		timer.startEvent("Search for a word (first occurence)");
		dict.searchWord("Apple");
		log.addEvent(timer.stopEvent());

		seneca::g_settings.m_show_all = true;
		timer.startEvent("Search for a word (all occurences)");
		dict.searchWord("Apple");
		log.addEvent(timer.stopEvent());
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}


	std::cout << '\n' << log;
	seneca::g_settings.m_time_units = "microseconds";
	std::cout << '\n' << log;
	seneca::g_settings.m_time_units = "milliseconds";
	std::cout << '\n' << log;
	seneca::g_settings.m_time_units = "seconds";
	std::cout << '\n' << log;

	return 0;
}
