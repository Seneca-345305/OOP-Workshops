// w4_p2.cpp - Containers
// 2021/12/02 - Miguel
// 2022/02/02 - Cornel

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <utility>
#include "shoppingCart.h"
#include "shoppingCart.h"  // intentional
#include "confirmationOrder.h"
#include "confirmationOrder.h" // intentional
#include "toy.h"
#include "toy.h" // intentional

// Cheching if header guards exists and follow convention.
#ifndef SENECA_TOY_H
    #error "The header guard for 'toy.h' doesn't follow the convention!"
#endif
#ifndef SENECA_SHOPPINGCART_H
    #error "The header guard for 'shoppingCart.h' doesn't follow the convention!"
#endif
#ifndef SENECA_CONFIRMATIONORDER_H
    #error "The header guard for 'confirmationOrder.h' doesn't follow the convention!"
#endif

int cout = 0; // prevents compilation if headers don't follow convention

int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; i++)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";

	const seneca::Toy** ppToys = nullptr;
	size_t count = 0;

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
					++count;
			}
		} while (file);

		ppToys = new const seneca::Toy*[count];
		count = 0;

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
					ppToys[count] = new seneca::Toy(strToy);
					++count;
				}
			}
		} while (file);
		file.close();
	}
	{
		std::cout << ">>>  T1: The Collection of Toys\n";
		std::cout << "==========:==========:==========:==========:==========:"
		             "==========:==========:==========:==========:==========\n";
		for (auto i = 0u; i < count; ++i)
		{
			std::cout << *ppToys[i];
		}
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
		             "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		std::cout << ">>>  T2: SC -> Testing the Constructor\n";
		std::cout << "==========:==========:==========:==========:==========:"
		             "==========:==========:==========:==========:==========\n";
		seneca::ShoppingCart child1("Kyle Patel", 8, ppToys, count);
		std::cout << child1;  // 1
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
		             "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";


		std::cout << ">>>  T3: SC -> Testing the Copy Constructor\n";
		std::cout << "==========:==========:==========:==========:==========:"
		             "==========:==========:==========:==========:==========\n";
		seneca::ShoppingCart child2(child1);
		std::cout << child1;  // 2
		std::cout << child2;  // 3
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
		             "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

		{
			std::cout << ">>>  T4: SC -> Testing the Copy Assignment Operator\n";
			std::cout << "==========:==========:==========:==========:==========:"
			             "==========:==========:==========:==========:==========\n";
			auto& refToChild = child2;
			refToChild = child2;  // this will check for self assignment
			std::cout << child2;  // 4
			seneca::ShoppingCart child3("Paul Sakuraba", 11, ppToys + 3, 4);
			child2 = child3;
			std::cout << child2;  // 5
			std::cout << child3;  // 6
			std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
			             "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
		}

		std::cout << ">>>  T5: SC -> Testing the Move Constructor\n";
		std::cout << "==========:==========:==========:==========:==========:"
		             "==========:==========:==========:==========:==========\n";
		auto& refToChild = child2;
		seneca::ShoppingCart child3(std::move(refToChild));
		std::cout << child2;  // 7
		std::cout << child3;  // 8
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
		             "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

		{
			std::cout << ">>>  T6: SC -> Testing the Move Assignment Operator\n";
			std::cout << "==========:==========:==========:==========:==========:"
			             "==========:==========:==========:==========:==========\n";
			auto& refToChild = child3;
			child3 = std::move(refToChild); // this will check for self assignment
			std::cout << child2;  //  9
			std::cout << child3;  // 10
			child2 = std::move(refToChild);
			std::cout << child2;  // 11
			std::cout << child3;  // 12
			std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
			             "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
		}
	}


	// Confirm Order
	{
		std::cout << ">>>  T7: CO -> Testing the Constructor\n";
		std::cout << "==========:==========:==========:==========:==========:"
		             "==========:==========:==========:==========:==========\n";
		seneca::ConfirmationOrder order1;
		std::cout << order1;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
		             "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

		std::cout << ">>>  T8: CO -> Testing the Operator Overloads\n";
		std::cout << "==========:==========:==========:==========:==========:"
		             "==========:==========:==========:==========:==========\n";
		order1 += *ppToys[5];
		order1 += *ppToys[6];
		order1 += *ppToys[6];
		((order1 += *ppToys[8]) += *ppToys[7]) += *ppToys[9];
		std::cout << order1;
		((order1 -= *ppToys[8]) -= *ppToys[9]);
		std::cout << order1;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
		             "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

		std::cout << ">>>  T9: CO -> Testing the Copy Constructor\n";
		std::cout << "==========:==========:==========:==========:==========:"
		             "==========:==========:==========:==========:==========\n";
		seneca::ConfirmationOrder order2(order1);
		std::cout << order1;
		std::cout << order2;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
		             "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

		auto& refToOrder = order2;
		refToOrder = order2; // tests for self assignment

		std::cout << ">>>  T10: CO -> Testing the Move Constructor\n";
		std::cout << "==========:==========:==========:==========:==========:"
		             "==========:==========:==========:==========:==========\n";
		seneca::ConfirmationOrder order3(std::move(order1));
		std::cout << order1;
		std::cout << order3;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
		             "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

		seneca::ConfirmationOrder& refOrder3 = order3;
		refOrder3 = std::move(order3);
	}

	{
		// Making a new array of pointers to toy.
		//   The toys in this array are not constant, so we must
		//   create copies of the original toy (which are constant)
		seneca::Toy* toys[]{
								new seneca::Toy(*ppToys[3]),
								new seneca::Toy(*ppToys[5]),
								new seneca::Toy(*ppToys[7]),
								new seneca::Toy(*ppToys[9])
							};

		std::cout << ">>>  T11: SC + CO -> Testing Relations\n";
		std::cout << "==========:==========:==========:==========:==========:"
		             "==========:==========:==========:==========:==========\n";
		seneca::ShoppingCart child("Tom Chow", 7, const_cast<const seneca::Toy**>(toys), 4u);
		seneca::ConfirmationOrder order;
		(order += *toys[0]) += *toys[1];
		(order += *toys[2]) += *toys[3];
		std::cout << child;
		std::cout << order;

		// updating some toys in main
		//   child should not be affected
		//   Confirmation order should be affected
		toys[0]->update(6);
		toys[2]->update(4);

		std::cout << "\nAfter main() updates some toys ...\n\n";

		std::cout << child;
		std::cout << order;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
		             "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

		// cleanup
		for (auto item : toys)
			delete item;
	}

	// cleanup
	for (auto i = 0u; i < count; ++i)
		delete ppToys[i];
	delete[] ppToys;

	return cout;
}
