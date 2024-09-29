#ifndef SENECA_ABILITIES_H
#define SENECA_ABILITIES_H
#include <iostream>
#include "character.h"

namespace seneca
{
	// for simplicity, the logic associated with the abilities is kept trivial.

	class Bersek {
		int m_cooldown{};
		int m_activeTime{};
	public:
		void useAbility(seneca::Character*)
		{
			// the ability is activated. The damage done will be increased
			// and the damage received will be reduced.
			--m_cooldown;
			if (m_cooldown <= 0)
			{
				std::cout << "    Bersek is activated for the next 6 seconds. Cooldown is 10 seconds.\n";
				m_activeTime = 6;
				m_cooldown = 10;
			}
		}

		void transformDamageDealt(int& dmg)
		{
			// modifies the damage dealt on others
			--m_activeTime;
			if (m_activeTime > 0)
			{
				std::cout << "    Bersek is active; increasing damage dealt from ["
					<< dmg << "] to [" << dmg * 2 << "].\n";
				dmg *= 2;
			}
		}

		void transformDamageReceived(int& dmg)
		{
			// modifies the damage received
			--m_activeTime;
			if (m_activeTime > 0)
			{
				std::cout << "    Bersek is active; reducing damage received from ["
					<< dmg << "] to [" << dmg / 2 << "].\n";
				dmg /= 2;
			}
		}
	};

	class Fireball {
		int m_cooldown{};
	public:
		void useAbility(seneca::Character*)
		{
			// fireball doesn't operate on self; do nothing
		}

		void transformDamageDealt(int& dmg)
		{
			// modifies the damage dealt on others
			--m_cooldown;
			if (m_cooldown == 0)
			{
				std::cout << "    Fireball has been triggered; increasing damage dealt by 500.\n";
				dmg += 500; // increases damage by 500
				m_cooldown = 20; // cannot be used again for the next 20 turns
			}
		}

		void transformDamageReceived(int&)
		{
			// fireball doesn't change the damage received; do nothing
		}
	};

	class Heal {
		int m_cooldown{};
	public:
		void useAbility(seneca::Character* src)
		{
			// heal maxes out the health
			--m_cooldown;
			if (m_cooldown <= 0)
			{
				std::cout << "    Heal is activated; setting health at ["
					<< src->getHealthMax() << "].\n";
				src->setHealth(src->getHealthMax());
				m_cooldown = 10;
			}
		}

		void transformDamageDealt(int&)
		{
			// Heal doesn't change the damage dealt; do nothing
		}

		void transformDamageReceived(int&)
		{
			// Heal doesn't change the damage received; do nothing
		}
	};
}

#endif
