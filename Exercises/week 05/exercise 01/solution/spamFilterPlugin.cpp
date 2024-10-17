// Exercise 5 - Pointers to Functions, Functors, Lambda Expressions, and Exceptions
#include <fstream>
#include <iostream>
#include <string>
#include "spamFilterPlugin.h"
#include "message.h"

namespace seneca
{
	SpamFilterPlugin::SpamFilterPlugin(const char* filename)
	{
		std::ifstream file(filename);
		if (file.is_open())
		{
			for (unsigned i = 0u; i < CAPACITY_SFP and file; ++i)
				std::getline(file, m_badWords[i]);
		}
		else
		{
			throw "File Not Found!";
		}
	}
	void SpamFilterPlugin::operator()(Message& msg)
	{
		// if the message is a spam, add "[SPAM] " at the begining of the subject line.
		for (std::string& word : m_badWords)
			if (word != "" and msg.m_subject.find(word) != std::string::npos)
			{
				++m_cntSpamFound;
				msg.m_subject = "[SPAM] " + msg.m_subject;
				break;
			}
	}
	void SpamFilterPlugin::showStats() const
	{
		std::cout << "[Spam Filter Plugin] Identified " << m_cntSpamFound << " spam messages.\n";
	}
}
