// Workshop 3 - Templates
// 2022/01/28 - If this code works, it was created by Cornel
//            - If it doesn't work, I don't know who wrote it.
// 2024/01/25 - See above

#ifndef SENECA_PAIR_H
#define SENECA_PAIR_H
#include <string>
#include <iomanip>

namespace seneca
{
	class Pair
	{
		std::string m_key{};
		std::string m_value{};
	public:
		const std::string& getKey() { return m_key; }
		const std::string& getValue() { return m_value; }
		Pair(const std::string& key, const std::string& value) : m_key{ key }, m_value{ value }{};

		// TODO: Add here the missing the prototypes for the members
		//           that are necessary if this class is to be used
		//           with the template classes described below.
		//       Implement them in the Pair.cpp file.
		Pair() = default;
		bool operator==(const Pair& other);
		friend std::ostream& operator<<(std::ostream& out, const Pair& item);
	};
}

#endif