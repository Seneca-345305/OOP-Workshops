// Exercise 5 - Pointers to Functions, Functors, Lambda Expressions, and Exceptions
#include <fstream>
#include <iostream>
#include "verifyIdentityPlugin.h"
#include "message.h"

namespace seneca
{
	VerifyIdentityPlugin::VerifyIdentityPlugin(const char* filename)
	{
		std::ifstream file(filename);
		if (file.is_open())
		{
			for (unsigned i = 0u; i < CAPACITY_VIP and file; ++i)
				std::getline(file, m_validUsers[i]);
		}
		else
		{
			throw "File Not Found!";
		}
	}

	void VerifyIdentityPlugin::operator()(Message& msg)
	{
		// if the message is sent by certain people, add "[TRUSTED] " in subject.
		for (std::string& user : m_validUsers)
			if (user != "" and user == msg.m_fromAddress)
			{
				msg.m_subject = "[TRUSTED] " + msg.m_subject;
				break;
			}
	}
	void VerifyIdentityPlugin::showStats() const
	{
		std::cout << "[Identity Checker Plugin] can validate identity for " << m_validUsers[0];
		for (unsigned i = 1u; i < CAPACITY_VIP and m_validUsers[i] != ""; ++i)
			std::cout << ", " << m_validUsers[i];
		std::cout << std::endl;
	}
}
