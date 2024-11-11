// Exercise - Multi-threading, Thread class 

#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream>
#include "ProcessData.h"
#include "ProcessData.h" // intentional

// Cheching if header guards exist and follow convention.
#ifndef SENECA_PROCESSDATA_H
    #error "The header guard for 'ProcessData.h' doesn't follow the convention!"
#endif

int cout = 0; // won't compile if headers don't follow convention regarding namespaces

void printHead(std::string str); // prints header text, embeds str into the text
void printFoot(); // prints footer text
void compareFiles(const std::string& fileName1, const std::string& fileName2);

int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; ++i)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";

	std::string fname_source = "data_int.dat", fname_target = "data_int_target.dat";
	// Source data file "data_int.dat" contains data in binary format. First 4 bytes (int size)
	//   in the file contain a value representing total number of data items stored in the file. From
	//   5th byte to the end of the file, the date items are stored consecutively, where each data item
	//   is stored in a memory space of 4 bytes (int size).
	// In the target data file "data_int_target.dat", the data read from "data_int.dat" will be saved
	//   in binary mode, in the same format.

	if (argc > 1)
		fname_source = argv[1];
	if (argc > 2)
		fname_target = argv[2];

	// The following code block creates function object `pd_obj` for the computation
	//   of average and variance through a single thread. During the function object
	//   creation, number of data items and the values of the data items are read
	//   and stored in instance variables. In addition to the filename `fname_source`,
	//   the constructor also receives the number of threads as the second argument,
	//   which is also stored in the instance variable. Some of the read data items
	//   are printed on standard output. The constructor initializes additional
	//   resource variables related to the implementation of multi-threading.
	// Invocation of the function object `pd_obj` divides the data into a number of
	//   parts, where the number of parts is equal to the number of threads.
	//   Multiple threads are used to compute average-factor for each part of the
	//   data by calling the function `computeAvgFactor` (provided). The calculated
	//   average-factors are added to compute total average. Computed total average
	//   is used as argument for `computeVarFactor`, which will compute
	//   variance-factors for each part of the data; multiple threads are used for
	//   this as well. The computed variance-factors are added to obtain total
	//   variance.
	// The arguments `avg` and `var` are passed by reference, so they carry the
	//   average and variance computed after the invocation of function object.
	// Invocation of the function object `pd_obj` also saves the data into the
	//   file `fname_target` supplied as argument.
	// Read the comments included in the implementation file `process_data.cpp`.
	{
		::printHead("Average and variance of record-values using 1 thread");
		std::chrono::steady_clock::time_point t_before, t_after;

		t_before = std::chrono::steady_clock::now();
		double avg = 0.0, var = 0.0;
		seneca::ProcessData pd_obj(fname_source, 1); // creates function object 
		if (pd_obj) {
			try {
				pd_obj(fname_target, avg, var); // invokes function object for "data_int.dat"
				::compareFiles(fname_source, fname_target);
			}
			catch (std::string& msg) {
				std::cout << msg << std::endl;
			}
		}
		t_after = std::chrono::steady_clock::now();
		std::cout << "Data statistics (\"" << fname_source << "\"):" << std::endl;
		std::cout.setf(std::ios::fixed);
		std::cout << " Average:  " << std::setw(16) << avg << std::endl;
		std::cout << " Variance: " << std::setw(16) << var << std::endl;
		std::cout.unsetf(std::ios::fixed);
		std::cout << "Time required to compute average and variance: "
			<< (std::chrono::duration_cast<std::chrono::milliseconds>(t_after - t_before)).count() 
			<< " milliseconds." << std::endl;
		::printFoot();
		std::cout << std::endl << std::endl;
	}

	// The following code block creates function object pd_obj for the computation of average and 
	//   variance through 2 threads. The function object is invoked to compute average and 
	//   variance.
	{
		::printHead("Average and variance of record-values using 2 threads");
		std::chrono::steady_clock::time_point t_before, t_after;

		t_before = std::chrono::steady_clock::now();
		double avg = 0.0, var = 0.0;
		seneca::ProcessData pd_obj(fname_source, 2); // creates function object 
		pd_obj(fname_target, avg, var); // invokes function object for "data_int.dat"
		t_after = std::chrono::steady_clock::now();

		std::cout << "Data statistics (\"" << fname_source << "\"):" << std::endl;
		std::cout.setf(std::ios::fixed);
		std::cout << " Average:  " << std::setw(16) << avg << std::endl;
		std::cout << " Variance: " << std::setw(16) << var << std::endl;
		std::cout.unsetf(std::ios::fixed);
		std::cout << "Time required to compute average and variance: "
			<< (std::chrono::duration_cast<std::chrono::milliseconds>(t_after - t_before)).count() 
			<< " milliseconds." << std::endl;
		::printFoot();
		std::cout << std::endl << std::endl;
	}

	// The following code block creates function object pd_obj for the computation of average and 
	//   variance through 4 threads. The function object is invoked to compute average and 
	//   variance.
	{
		::printHead("Average and variance of record-values using 4 threads");
		std::chrono::steady_clock::time_point t_before, t_after;

		t_before = std::chrono::steady_clock::now();
		double avg = 0.0, var = 0.0;;
		seneca::ProcessData pd_obj(fname_source, 4); // creates function object 
		pd_obj(fname_target, avg, var); // invokes function object for "data_int.dat"
		t_after = std::chrono::steady_clock::now();

		std::cout << "Data statistics (\"" << fname_source << "\"):" << std::endl;
		std::cout.setf(std::ios::fixed);
		std::cout << " Average:  " << std::setw(16) << avg << std::endl;
		std::cout << " Variance: " << std::setw(16) << var << std::endl;
		std::cout.unsetf(std::ios::fixed);
		std::cout << "Time required to compute average and variance: "
			<< (std::chrono::duration_cast<std::chrono::milliseconds>(t_after - t_before)).count() 
			<< " milliseconds." << std::endl;
		::printFoot();
	}

	return cout;
}

void printHead(std::string str)
{
	std::cout << std::setw(90) << std::setfill('=') << '=' << std::endl << std::setfill(' ');
	std::cout << std::setw(45 - str.length() / 2) << ' ' << str << std::endl;
	std::cout << std::setw(90) << std::setfill('-') << '-' << std::endl << std::setfill(' ');
}

void printFoot()
{
	std::cout << std::setw(90) << std::setfill('=') << '=' << std::endl;
}

void compareFiles(const std::string& fileName1, const std::string& fileName2)
{
	std::ifstream file1(fileName1), file2(fileName2);
	int cnt = 0;
	while (file1 && file2)
	{
		if (file1.get() != file2.get())
			throw std::string("The output file doesn't have the correct binary content as the input file.\n"
			                  "  Byte " + std::to_string(cnt) + " is wrong.\n"
			                  "  Check the 'operator()' implementation to fix.\n");
		++cnt;
	}
	std::cout << "Read [" << cnt << "] bytes from the files; the content is the same.\n";
}
