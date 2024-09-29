// Workshop 3 - Templates
// 2022/01/28 - If this code works, it was created by Cornel
//            - If it doesn't work, I don't know who wrote it.
// 2024/01/25 - See above

#include <iostream>
#include "Pair.h"

namespace seneca
{
	bool Pair::operator==(const Pair& other)
	{
		return this->m_key == other.m_key;
	}

	std::ostream& operator<<(std::ostream& out, const Pair& item)
	{
		out << std::setw(20) << item.m_key << ": " << item.m_value;
		return out;
	}
}
