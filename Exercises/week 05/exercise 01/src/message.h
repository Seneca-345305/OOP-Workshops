#ifndef SENECA_MESSAGE_H
#define SENECA_MESSAGE_H
#include <string>

namespace seneca
{
	/// <summary>
	/// Stores information about an email message.
	/// </summary>
	struct Message
	{
		/// <summary>
		/// The email address of the person who receives the message.
		/// </summary>
		std::string m_toAddress;

		/// <summary>
		/// The email address of the person who sent the message.
		/// </summary>
		std::string m_fromAddress;

		/// <summary>
		/// The name of the person who sent the message.
		/// </summary>
		std::string m_fromName;

		/// <summary>
		/// The subject of the message.
		/// </summary>
		std::string m_subject;

		/// <summary>
		/// The date and time of this email.
		/// </summary>
		std::string m_date;
	};
}
#endif
