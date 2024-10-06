// toy.h - class declaration for a toy
#ifndef SENECA_TOY_H
#define SENECA_TOY_H

#include <iostream>
#include <string>

namespace seneca
{
	class Toy
	{
		unsigned int m_id = 0;
		std::string m_name = "";
		int m_num = 0;
		double m_price = 0.0;
		double hst = 0.13;

		void trim(std::string& str) const;
	public:
		Toy() = default;
		Toy(const std::string& toy);
		void update(int numItems) { m_num = numItems; }

		friend std::ostream& operator<<(std::ostream& out, const Toy& toy);
	};
}
#endif// SENECA_TOY_H
