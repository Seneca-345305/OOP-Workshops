#ifndef SENECA_PROTEINDATABASE_H
#define SENECA_PROTEINDATABASE_H

#include <string>

namespace seneca
{
	class ProteinDatabase
	{
		std::string* m_proteinUIDs{ nullptr };
		std::string* m_proteinSequences{ nullptr };
		size_t m_cnt{ 0 };
	public:
		ProteinDatabase();
		ProteinDatabase(const std::string&);
		ProteinDatabase(const ProteinDatabase&);
		ProteinDatabase(ProteinDatabase&&) noexcept;
		ProteinDatabase& operator=(const ProteinDatabase&);
		ProteinDatabase& operator=(ProteinDatabase&&) noexcept;

		~ProteinDatabase();

		size_t size() const { return m_cnt; }
		std::string operator[](size_t idx) const;
		std::string getUID(size_t idx) const;
	};
}
#endif
