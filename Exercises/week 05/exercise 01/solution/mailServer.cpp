// Exercise 5 - Pointers to Functions, Functors, Lambda Expressions, and Exceptions
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <utility>
#include "mailServer.h"
#include "message.h"
#include "plugin.h"

namespace seneca
{
	MailServer::MailServer(const char* name, const char* address) : m_userName{name}, m_userAddress{address}
	{
	}

	MailServer::MailServer(const MailServer& other)
	{
		*this = other;
	}

	MailServer& MailServer::operator=(const MailServer& other)
	{
		if (this != &other)
		{
			delete[] m_inbox;

			this->m_userName = other.m_userName;
			this->m_userAddress = other.m_userAddress;
			this->m_plugins[0] = other.m_plugins[0];
			this->m_plugins[1] = other.m_plugins[1];
			this->m_cnt = other.m_cnt;

			if (m_cnt != 0)
			{
				this->m_inbox = new Message[m_cnt];
				for (auto i = 0u; i < m_cnt; ++i)
					this->m_inbox[i] = other.m_inbox[i];
			}
			else
				m_inbox = nullptr;
		}
		return *this;
	}

	MailServer::MailServer(MailServer&& other) noexcept
	{
		*this = std::move(other);
	}

	MailServer& MailServer::operator=(MailServer&& other) noexcept
	{
		if (this != &other)
		{
			delete[] m_inbox;

			this->m_userName = other.m_userName;
			this->m_userAddress = other.m_userAddress;
			this->m_plugins[0] = other.m_plugins[0];
			this->m_plugins[1] = other.m_plugins[1];
			this->m_cnt = other.m_cnt;

			this->m_inbox = other.m_inbox;
			other.m_inbox = nullptr;
		}
		return *this;
	}

	MailServer::~MailServer()
	{
		delete[] m_inbox;
	}

	void MailServer::receiveMail(Message msg)
	{
		if (msg.m_toAddress != this->m_userAddress)
		{
			// the message is not for this user, raise an exception to inform the client
			throw "The message is for another user.";
		}

		// resize the array and add the new message
		Message* tmp = new Message[m_cnt + 1];
		for (auto i = 0u; i < m_cnt; ++i)
			tmp[i] = m_inbox[i];
		tmp[m_cnt] = msg;
		delete[] m_inbox;
		m_inbox = tmp;
		++m_cnt;

		// run the plugins on the new message
		for (Plugin* plugin : m_plugins)
			if (plugin != nullptr)
				(*plugin)(m_inbox[m_cnt - 1]);

		// inform the observer
		if (onNewMailArrived != nullptr)
			onNewMailArrived(m_inbox[m_cnt - 1]);
	}

	void MailServer::addPlugin(Plugin* thePlugin)
	{
		if (thePlugin != nullptr)
		{
			if (m_plugins[0] == nullptr)
				m_plugins[0] = thePlugin;
			else if (m_plugins[1] == nullptr)
				m_plugins[1] = thePlugin;
			else { /* nothing to do */ }
		}
	}

	void MailServer::setObserver(void(*observer)(const Message&))
	{
		this->onNewMailArrived = observer;
	}

	Message& MailServer::operator[](size_t idx)
	{
		if (idx < this->m_cnt)
			return m_inbox[idx];
		throw std::out_of_range("Index " + std::to_string(idx) + " is out of bounds.");
	}

	size_t MailServer::getInboxSize() const
	{
		return m_cnt;
	}

	void MailServer::showInbox() const
	{
		for (unsigned i = 0u; i < m_cnt; ++i)
		{
			auto& email = m_inbox[i];

			std::cout << std::setw(20) << email.m_fromName << "  ";
			std::cout.setf(std::ios::left);
			std::cout << std::setw(40) << email.m_fromAddress << "  ";
			std::cout << std::setw(15) << email.m_date.substr(0, 10) << "  ";
			std::cout.unsetf(std::ios::left);
			std::cout << email.m_subject << std::endl;
		}
	}
}
