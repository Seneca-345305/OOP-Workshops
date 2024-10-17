// Exercise 5 - Pointers to Functions, Functors, Lambda Expressions, and Exceptions
#ifndef SENECA_VERIFYIDENTITYPLUGIN_H
#define SENECA_VERIFYIDENTITYPLUGIN_H
#include <string>
#include "plugin.h"

namespace seneca
{
	constexpr size_t CAPACITY_VIP = 10u;

	class VerifyIdentityPlugin : public Plugin
	{
		std::string m_validUsers[CAPACITY_VIP];
	public:
		VerifyIdentityPlugin(const char* filename);
		void operator()(Message& msg) override;
		void showStats() const override;
	};
}
#endif
