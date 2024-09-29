// Workshop 3 - Templates
// 2022/01/28 - If this code works, it was created by Cornel
//            - If it doesn't work, I don't know who wrote it.
// 2024/01/25 - See above

#ifndef SENECA_SET_H
#define SENECA_SET_H
#include <cmath>     // for std::fabs()
#include "Collection.h"

namespace seneca
{
	constexpr int SET_CAPACITY = 100;

	// A set is a collection without duplicates
	template<typename T>
	class Set : public Collection<T, SET_CAPACITY>
	{
	public:
		bool add(const T& item) override
		{
			for (auto i = 0u; i < this->size(); ++i)
			{
				if ((*this)[i] == item)
					return false;
			}

			return Collection<T, SET_CAPACITY>::add(item);
		}
	};

	// Specialization for double: numbers that are 0.01 from eachother are considered the same
	template<>
	bool Set<double>::add(const double& item)
	{
		double epsilon = 0.01;

		for (auto i = 0u; i < this->size(); ++i)
		{
			if (std::fabs((*this)[i] - item) <= epsilon)
				return false;
		}

		return Collection<double, SET_CAPACITY>::add(item);
	}
}

#endif
