#include <utility>
#include <ostream>
#include "shoppingCart.h"

namespace seneca
{
	ShoppingCart::ShoppingCart(const std::string& name, int age, const Toy* toys[], size_t count)
	{
		this->m_childName = name;
		this->m_childAge = age;
		this->m_count = count;
		this->m_pToys = new const Toy*[m_count];
		for (auto i = 0u; i < m_count; ++i)
			this->m_pToys[i] = new Toy(*toys[i]);
	}
	ShoppingCart::ShoppingCart(const ShoppingCart& other)
	{
		*this = other;
	}
	ShoppingCart& ShoppingCart::operator=(const ShoppingCart& other)
	{
		if (this != &other)
		{
			for (auto i = 0u; i < m_count; ++i)
				delete this->m_pToys[i];
			delete[] this->m_pToys;

			m_childName = other.m_childName;
			m_childAge = other.m_childAge;
			m_count = other.m_count;

			if (m_count > 0)
			{
				this->m_pToys = new const Toy * [m_count];
				for (auto i = 0u; i < m_count; ++i) {
					this->m_pToys[i] = new Toy(*other.m_pToys[i]);
				}
			}
			else
				this->m_pToys = nullptr;
		}
		return *this;
	}
	ShoppingCart::ShoppingCart(ShoppingCart&& other) noexcept
	{
		*this = std::move(other);
	}
	ShoppingCart& ShoppingCart::operator=(ShoppingCart&& other) noexcept
	{
		if (this != &other)
		{
			for (auto i = 0u; i < m_count; ++i)
				delete this->m_pToys[i];
			delete[] this->m_pToys;

			m_childName = other.m_childName;
			m_childAge = other.m_childAge;
			m_count = other.m_count;

			this->m_pToys = other.m_pToys;
			other.m_childName = "";
			other.m_childAge = 0;
			other.m_count = 0;
			other.m_pToys = nullptr;
		}
		return *this;
	}
	ShoppingCart::~ShoppingCart()
	{
		for (auto i = 0u; i < m_count; ++i)
			delete this->m_pToys[i];
		delete[] this->m_pToys;
	}

	std::ostream& operator<<(std::ostream& os, const ShoppingCart& cart)
	{
		static size_t callCnt = 0;
		os << "--------------------------\n";
		if (cart.m_childName != "")
		{
			os << "Order " << ++callCnt << ": Shopping for " << cart.m_childName << " "
			   << cart.m_childAge << " years old (" << cart.m_count << " toys)\n";
			os << "--------------------------\n";
			if (cart.m_count == 0)
				os << "Empty shopping cart!\n";
			for (auto i = 0u; i < cart.m_count; ++i)
				os << *cart.m_pToys[i];
		}
		else
			os << "Order " << ++callCnt << ": This shopping cart is invalid.\n";
		os << "--------------------------\n";
		return os;
	}
}
