#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <utility>
#include "Toy.h"
#include "Toy.h" // intentional

int cout = 0; // won't compile if headers don't follow convention

int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; i++)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n";

	seneca::Toy** ppToys = nullptr;
	size_t cnt = 0;

	// Process the file
	if (argc > 1) {
		std::ifstream file(argv[1]);
		if (!file)
		{
			std::cerr << "ERROR: Cannot open file [" << argv[1] << "].\n";
			return 1;
		}

		std::string strToy;
		// count how many records are in the file
		do
		{
			std::getline(file, strToy);

			// if the previous operation failed, the "file" object is
			//   in error mode
			if (file)
			{
				// Check if this is a commented line.
				//   In the input file, commented lines start with '#'
				if (strToy[0] != '#')
					++cnt;
			}
		} while (file);

		ppToys = new seneca::Toy * [cnt];
		cnt = 0;

		// read again from the file, but this time load and store data
		file.clear();
		file.seekg(std::ios::beg);
		do
		{
			std::getline(file, strToy);

			// if the previous operation failed, the "file" object is
			//   in error mode
			if (file)
			{
				// Check if this is a commented line.
				//   In the input file, commented lines start with '#'
				if (strToy[0] != '#')
				{
					ppToys[cnt] = new seneca::Toy(strToy);
					++cnt;
				}
			}
		} while (file);
		file.close();
	}
	std::cout << "\nToys\n--------------------------\n";
	for (auto i = 0u; i < cnt; ++i)
	{
		std::cout << *ppToys[i];
	}
	std::cout << "--------------------------\n\n";

	// modify the amount for some toys
	if (cnt > 2)
	{
		ppToys[0]->update(6);
		ppToys[2]->update(4);
	}

	std::cout << "\nUpdated Toys\n--------------------------\n";
	for (auto i = 0u; i < cnt; ++i)
	{
		std::cout << *ppToys[i];
	}
	std::cout << "--------------------------\n\n";

	// cleanup
	for (auto i = 0u; i < cnt; ++i)
		delete ppToys[i];
	delete[] ppToys;

	return cout;
}
