// ConfirmationOrder.cpp - function definitions for order confirmation

#include <utility>
#include "confirmationOrder.h"

namespace seneca
{
	ConfirmationOrder::ConfirmationOrder(const ConfirmationOrder& other)
	{
		*this = other;
	}
	ConfirmationOrder& ConfirmationOrder::operator=(const ConfirmationOrder& other)
	{
		if (this != &other)
		{
			delete[] this->m_pToys;

			this->m_count = other.m_count;

			if (this->m_count > 0)
			{
				this->m_pToys = new const Toy * [m_count];
				for (auto i = 0u; i < this->m_count; ++i)
					this->m_pToys[i] = other.m_pToys[i];
			}
			else
				this->m_pToys = nullptr;
		}
		return *this;
	}
	ConfirmationOrder::ConfirmationOrder(ConfirmationOrder&& other) noexcept
	{
		*this = std::move(other);
	}
	ConfirmationOrder& ConfirmationOrder::operator=(ConfirmationOrder&& other) noexcept
	{
		if (this != &other)
		{
			delete[] this->m_pToys;

			this->m_count = other.m_count;

			this->m_pToys = other.m_pToys;
			other.m_pToys = nullptr;
			other.m_count = 0;
		}
		return *this;
	}

	ConfirmationOrder::~ConfirmationOrder()
	{
		delete[] this->m_pToys;
	}

	ConfirmationOrder& ConfirmationOrder::operator+=(const Toy& toy)
	{
		bool found = false;
		for (auto i = 0u; i < m_count && found == false; ++i)
			if (&toy == m_pToys[i])
				found = true;

		if (found == false)
		{
			// resize & add
			const Toy** tmp = nullptr;
			tmp = new const Toy * [m_count + 1];
			for (auto i = 0u; i < m_count; ++i)
				tmp[i] = m_pToys[i];
			tmp[m_count] = &toy;

			++m_count;
			delete[] m_pToys;
			m_pToys = tmp;
		}

		return *this;
	}

	ConfirmationOrder& ConfirmationOrder::operator-=(const Toy& toy)
	{
		auto idx = 0u;
		for (/* not needed */; idx < m_count; ++idx)
			if (&toy == m_pToys[idx])
				break;

		if (idx < m_count)
		{
			// Actual resize
			const Toy** tmp = nullptr;
			if (m_count > 1u)
			{
				// resize
				tmp = new const Toy * [m_count - 1];
				for (auto i = 0u; i < idx; ++i)
					tmp[i] = m_pToys[i];
				for (auto i = idx; i < m_count - 1; ++i)
					tmp[i] = m_pToys[i + 1];
			}
			delete[] m_pToys;
			m_pToys = tmp;
			--m_count;

			// Fake resize
			//for (auto i = idx; i < m_count - 1; ++i)
			//	m_pToys[i] = m_pToys[i + 1];
			//m_pToys[m_count - 1] = nullptr;
			//--m_count;
		}
		return *this;
	}

	std::ostream& operator<<(std::ostream& os, const ConfirmationOrder& order)
	{
		os << "--------------------------\n";
		os << "Confirmations to Send (" << order.m_count << " toys)\n";
		os << "--------------------------\n";
		if (order.m_count == 0)
			os << "There are no confirmations to send!\n";
		for (auto i = 0u; i < order.m_count; ++i)
			os << *(order.m_pToys[i]);
		os << "--------------------------\n";
		return os;
	}
}
