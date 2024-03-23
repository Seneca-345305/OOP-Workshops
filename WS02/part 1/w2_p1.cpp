#include <iostream>
#include <iomanip>
#include <utility>
#include <string>
#include "StringSet.h"
#include "StringSet.h" // intentional
#include "TimedEvents.h"
#include "TimedEvents.h" // intentional

// Cheching if header guards exist and follow convention.
#ifndef SENECA_STRINGSET_H
    #error "The header guard for 'StringSet.h' doesn't follow the convention!"
#endif
#ifndef SENECA_TIMEDEVENTS_H
    #error "The header guard for 'TimedEvents.h' doesn't follow the convention!"
#endif

enum ExitCodes
{
	ALL_GOOD                  = 0,  // nothing is wrong
	ERR_INSUFICIENT_ARGUMENTS = 1,  // the application received too few arguments
	ERR_TOO_MANY_ARGUMENTS    = 2,  // the application received too many arguments
};

int cout = ExitCodes::ALL_GOOD; // won't compile if headers don't follow convention regarding namespaces

int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; i++)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";

	if (argc == 1)
	{
		std::cerr << "ERROR: Missing file name!\n";
		return ExitCodes::ERR_INSUFICIENT_ARGUMENTS;
	}
	else if (argc != 2)
	{
		std::cerr << "ERROR: Too many arguments!\n";
		return ExitCodes::ERR_TOO_MANY_ARGUMENTS;
	}

	seneca::TimedEvents t;
	{
		t.startClock();
		seneca::StringSet a;
		t.stopClock();
		t.addEvent("  0-arg Constructor");
		std::cout << "  0-arg Constructor - a.size = "
			<< std::setw(7) << a.size() << " strings -> ";
		std::cout << std::setw(20) << "(a) String     1: [" << a[  0] << "]\n";
		std::cout << std::setw(70) << "(a) String   100: [" << a[ 99] << "]\n";
		std::cout << std::setw(70) << "(a) String  1000: [" << a[999] << "]\n";
		std::cout << std::setw(70) << "(a) String  last: [" << a[a.size() - 1] << "]\n";
		std::cout << std::setw(70) << "(a) String last+: [" << a[a.size()] << "]\n\n";


		t.startClock();
		seneca::StringSet b(argv[1]);
		t.stopClock();
		t.addEvent("  1-arg Constructor");
		std::cout << "  1-arg Constructor - b.size = "
			<< std::setw(7) << b.size() << " strings -> ";
		std::cout << std::setw(20) << "(b) String     1: [" << b[  0] << "]\n";
		std::cout << std::setw(70) << "(b) String   100: [" << b[ 99] << "]\n";
		std::cout << std::setw(70) << "(b) String  1000: [" << b[999] << "]\n";
		std::cout << std::setw(70) << "(b) String  last: [" << b[b.size() - 1] << "]\n";
		std::cout << std::setw(70) << "(b) String last+: [" << b[b.size()] << "]\n\n";


		t.startClock();
		seneca::StringSet c{ b };
		t.stopClock();
		t.addEvent("  Copy Constructor");
		std::cout << "  Copy Constructor  - c.size = "
			<< std::setw(7) << c.size() << " strings -> ";
		std::cout << std::setw(20) << "(c) String     1: [" << c[0] << "]\n";
		std::cout << std::setw(70) << "(c) String   100: [" << c[99] << "]\n";
		std::cout << std::setw(70) << "(c) String  1000: [" << c[999] << "]\n";
		std::cout << std::setw(70) << "(c) String  last: [" << c[c.size() - 1] << "]\n";
		std::cout << std::setw(70) << "(c) String last+: [" << c[c.size()] << "]\n\n";


		t.startClock();
		a = b;
		t.stopClock();
		t.addEvent("  Copy Assignment");
		std::cout << "  Copy Assignment   - a.size = "
			<< std::setw(7) << a.size() << " strings -> ";
		std::cout << std::setw(20) << "(a) String     1: [" << a[0] << "]\n";
		std::cout << std::setw(70) << "(a) String   100: [" << a[99] << "]\n";
		std::cout << std::setw(70) << "(a) String  1000: [" << a[999] << "]\n";
		std::cout << std::setw(70) << "(a) String  last: [" << a[a.size() - 1] << "]\n";
		std::cout << std::setw(70) << "(a) String last+: [" << a[a.size()] << "]\n\n";


		t.startClock();
	}
	t.stopClock();
	t.addEvent("  Destructor");

	std::cout << t;
	
	return cout;
}
