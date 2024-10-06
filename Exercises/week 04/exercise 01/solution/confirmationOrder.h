// ConfirmationOrder.h - class declaration for a confirmation order system

#ifndef SENECA_CONFIRMATIONORDER_H
#define SENECA_CONFIRMATIONORDER_H
#include <ostream>
#include "toy.h"

namespace seneca
{
	class ConfirmationOrder
	{
		const seneca::Toy** m_pToys{};
		size_t m_count{};
	public:
		ConfirmationOrder() = default;
		~ConfirmationOrder();
		ConfirmationOrder(const ConfirmationOrder& other);
		ConfirmationOrder& operator=(const ConfirmationOrder& other);
		ConfirmationOrder(ConfirmationOrder&& other) noexcept;
		ConfirmationOrder& operator=(ConfirmationOrder&& other) noexcept;

		ConfirmationOrder& operator+=(const Toy& toy);
		ConfirmationOrder& operator-=(const Toy& toy);

		friend std::ostream& operator<<(std::ostream& os, const ConfirmationOrder& order);
	};
}
#endif// SENECA_CONFIRMORDER_H
