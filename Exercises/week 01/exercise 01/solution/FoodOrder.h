#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H

#include <iostream>

extern double g_taxrate;        // tax rate to calculate total price
extern double g_dailydiscount;  // flat discount on daily specials

namespace seneca
{
	class FoodOrder
	{
		char m_customerName[10]{};
		char* m_orderDesc{};
		double m_price{};
		bool m_dailyspecial{};
	public:
		void read(std::istream &is);
		void display() const;

		FoodOrder(){};
		FoodOrder(const FoodOrder& src);
		FoodOrder& operator=(const FoodOrder& src);
		~FoodOrder();
	};

}
#endif
