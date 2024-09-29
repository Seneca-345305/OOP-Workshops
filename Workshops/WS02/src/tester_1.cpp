#include <iostream>
#include <iomanip>
#include "weapons.h"
#include "weapons.h"        // intentional
#include "abilities.h"
#include "abilities.h"      // intentional
#include "health.h"
#include "health.h"         // health
#include "character.h"
#include "character.h"      // intentional
#include "team.h"
#include "team.h"           // intentional
#include "guild.h"
#include "guild.h"          // intentional
#include "barbarian.h"
#include "barbarian.h"      // intentional
#include "rogue.h"
#include "rogue.h"          // intentional
#include "archer.h"
#include "archer.h"         // intentional

// Cheching if header guards exist and follow convention.
#ifndef SENECA_CHARACTER_H
    #error "The header guard for 'character.h' doesn't follow the convention!"
#endif
#ifndef SENECA_BARBARIAN_H
    #error "The header guard for 'barbarian.h' doesn't follow the convention!"
#endif
#ifndef SENECA_ROGUE_H
    #error "The header guard for 'rogue.h' doesn't follow the convention!"
#endif
#ifndef SENECA_ARCHER_H
    #error "The header guard for 'archer.h' doesn't follow the convention!"
#endif
#ifndef SENECA_TEAM_H
    #error "The header guard for 'team.h' doesn't follow the convention!"
#endif
#ifndef SENECA_GUILD_H
    #error "The header guard for 'guild.h' doesn't follow the convention!"
#endif
#ifndef SENECA_WEAPONS_H
    #error "The header guard for 'weapons.h' doesn't follow the convention!"
#endif
#ifndef SENECA_ABILITIES_H
    #error "The header guard for 'abilities.h' doesn't follow the convention!"
#endif
#ifndef SENECA_HEALTH_H
    #error "The header guard for 'health.h' doesn't follow the convention!"
#endif

int cout = 0; // won't compile if headers don't follow convention regarding namespaces

int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "------------------------------------------------------\n";
	for (int i = 0; i < argc; ++i)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "------------------------------------------------------\n\n";

	seneca::Team team_1("The Procrastinators");
	seneca::Team team_2("The King's Guard");

	{
		seneca::Rogue<seneca::SuperHealth, seneca::Heal, seneca::Fireball> ch_1("Quick Silver", 950, 33, 77);
		seneca::Rogue<double, seneca::Fireball, seneca::Fireball> ch_2("Rogue Ronin", 800, 50, 50);
		seneca::Rogue<seneca::InfiniteHealth, seneca::Bersek, seneca::Bersek> ch_3("Ghost Blade", 20, 10, 1);

		seneca::Archer<seneca::Crossbow> ch_4("Lethal Bunny", 1000, 200, 111, seneca::Crossbow{ 124 });
		seneca::Archer<seneca::Crossbow> ch_5("Nova Burst", 1234, 150, 123, {});
		seneca::Archer<seneca::Bow> ch_6("Kill Switch", 2000, 222, 67, seneca::Bow{ 210 });

		seneca::Barbarian<double, seneca::Bersek, seneca::Sword> ch_7("Master Chief",   1000, 100, 10, seneca::Sword{ 23 }, seneca::Sword{ 20 });
		seneca::Barbarian<double, seneca::Heal,   seneca::Axe>   ch_8("Mercy Less",     1200,  80,  8, {}, {});
		seneca::Barbarian<seneca::InfiniteHealth, seneca::Fireball, seneca::BareHands> ch_9("Mecha Doom", 100, 50, 0, {}, {});
		seneca::Barbarian<double, seneca::Fireball, seneca::Sword> ch_10("Flame Princess", 100, 100, 100, {}, {});

		seneca::Barbarian<double, seneca::Bersek,   seneca::Sword> ch_11("Big Boss",       50, 200, 23, {}, {});
		seneca::Barbarian<double, seneca::Bersek,   seneca::Sword> ch_12("Loot Goblin",    60, 180, 34, {}, {});
		seneca::Barbarian<double, seneca::Bersek,   seneca::Sword> ch_13("Toxic Terror",   70, 160, 45, {}, {});
		seneca::Barbarian<double, seneca::Bersek,   seneca::Sword> ch_14("Plasma Cannon",  80, 140, 56, {}, {});
		seneca::Barbarian<double, seneca::Bersek,   seneca::Sword> ch_15("Nebula",         90, 120, 67, {}, {});
		seneca::Barbarian<double, seneca::Bersek,   seneca::Sword> ch_16("Tomb Raider",   100, 100, 78, {}, {});
		seneca::Barbarian<double, seneca::Bersek,   seneca::Sword> ch_17("Last Guardian", 110,  80, 89, {}, {});
		seneca::Barbarian<double, seneca::Bersek,   seneca::Sword> ch_18("Serpent King",  120,  60, 101, {}, {});
		seneca::Barbarian<double, seneca::Bersek,   seneca::Sword> ch_19("Morpheus",      130,  40, 112, {}, {});
		seneca::Barbarian<double, seneca::Bersek,   seneca::Sword> ch_20("Razor Sharp",   140,  20, 123, {}, {});

		team_1.addMember(&ch_1);
		team_1.addMember(&ch_1); // attempting to add again the same item; should not add
		team_1.addMember(&ch_2);
		team_1.addMember(&ch_4);
		team_1.addMember(&ch_7);
		team_1.addMember(&ch_9);
		team_1.addMember(&ch_9); // attempting to add again the same item; should not add

		team_2.addMember(&ch_3);
		team_2.addMember(&ch_5);
		team_2.addMember(&ch_6);
		team_2.addMember(&ch_6); // attempting to add again the same item; should not add
		team_2.addMember(&ch_8);
		team_2.addMember(&ch_10);

		// local scope ends here, all `ch_*` characters will go out of scope
		//   This should cause no problem because the would have already made copies.
	}

	{
		std::cout << "T1: Building the Teams of Characters\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		team_1.showMembers();
		team_2.showMembers();
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	seneca::Guild guild_1("Spartans");
	seneca::Guild guild_2("Syndicate");

	{
		std::cout << "T2: Increased Health for Guild Members\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		guild_1.addMember(team_1[2]); // the health of this character should be increased when in a guild
		guild_1.addMember(team_1[2]); // attempting to add again the same item; should not add
		guild_1.addMember(team_1[1]);
		guild_1.addMember(team_2[4]);
		team_1.showMembers(); // should show increased health for guild characters
		guild_1.showMembers();
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		std::cout << "T3: One Guild Member Leaves Guild\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		guild_1.removeMember("Lethal Bunny"); // remove it from guild
		guild_1.removeMember("Mister Nobody"); // noop; not in the guild
		team_1.showMembers(); // Lethal Bunny should have original health
		guild_1.showMembers();
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}
	{
		std::cout << "T4: Check Copy Constructor in Team\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		seneca::Team copy(team_1);
		copy.showMembers();
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}
	{
		std::cout << "T5: Check Copy Assignment Operator in Team\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		seneca::Team copy("Toronto Angels");
		copy = team_1;
		copy.showMembers();

		copy = copy; // check for self assignment

		copy = team_2;
		copy.showMembers();
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}
	{
		std::cout << "T6: Check the Move Operations in Team\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		seneca::Team copy(std::move(team_1));
		team_1.showMembers();
		copy.showMembers();
		team_1 = std::move(copy);
		team_1.showMembers();
		copy.showMembers();
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		std::cout << "T7: Check Copy Constructor in Guild\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		seneca::Guild copy(guild_1);
		copy.showMembers();
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}
	{
		std::cout << "T8: Check Copy Assignment Operator in Guild\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		seneca::Guild copy("Professional Puppies");
		copy = guild_1;
		copy.showMembers();

		copy = copy; // check for self assignment

		copy = guild_2;
		copy.showMembers();
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}
	{
		std::cout << "T9: Check the Move Operations in Guild\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		seneca::Guild copy(std::move(guild_1));
		guild_1.showMembers();
		copy.showMembers();
		guild_1 = std::move(copy);
		guild_1.showMembers();
		copy.showMembers();
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	{
		// Master Chief wins in 10 rounds
		std::cout << "T10: Epic battle between Master Chief and Mercy Less\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		int i = 1;
		auto& first = *(team_1[3]);
		auto& second = *(team_2[3]);
		while (first.isAlive() and second.isAlive())
		{
			std::cout << "[Round " << i++ << "]\n";
			first.attack(&second);
			second.attack(&first);
			std::cout << "---\n";
			std::cout << first << std::endl << second << std::endl;
			std::cout << "---\n\n";
		}
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

	// heal Master Chief
	team_1[3]->setHealth(team_1[3]->getHealthMax());
	// Mercy Less joins a guild -> health increase
	guild_2.addMember(team_2[3]);

	{
		// repeat the battle, but now Mercy Less is in a guild
		// Mercy Less wins in 13 rounds
		std::cout << "T11: Epic battle between Master Chief and Mercy Less\n";
		std::cout << "==========:==========:==========:==========:==========\n";
		int i = 1;
		auto& first = *(team_1[3]);
		auto& second = *(team_2[3]);
		while (first.isAlive() and second.isAlive())
		{
			std::cout << "[Round " << i++ << "]\n";
			first.attack(&second);
			second.attack(&first);
			std::cout << "---\n";
			std::cout << first << std::endl << second << std::endl;
			std::cout << "---\n\n";
		}
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}
}
