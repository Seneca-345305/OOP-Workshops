#ifndef SENECA_SHOPPINGCART_H
#define SENECA_SHOPPINGCART_H

#include <ostream>
#include "toy.h"

namespace seneca
{
	//manages a collection of toys
	class ShoppingCart
	{
		std::string m_childName{};
		int m_childAge{};
		const seneca::Toy** m_pToys{};
		size_t m_count{};
	public:
		ShoppingCart(const std::string& name, int age, const Toy* toys[], size_t count);
		ShoppingCart(const ShoppingCart& other);
		ShoppingCart& operator=(const ShoppingCart& other);
		ShoppingCart(ShoppingCart&& other) noexcept;
		ShoppingCart& operator=(ShoppingCart&& other) noexcept;
		~ShoppingCart();

		friend std::ostream& operator<<(std::ostream& os, const ShoppingCart& cart);
	};
}
#endif// SENECA_SHOPPINGCART_H
