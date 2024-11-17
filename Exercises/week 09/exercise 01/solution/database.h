#ifndef SENECA_DATABASE_H
#define SENECA_DATABASE_H

#include <fstream>   // std::ifstream
#include <iostream>  // std::cout
#include <iomanip>   // std::setw
#include <algorithm> // std::replace
#include <memory>    // std::shared_ptr
#include <string>    // std::string

namespace seneca
{
	enum class Err_Status
	{
		Err_Success,
		Err_NotFound,
		Err_OutOfMemory
	};

	constexpr unsigned int MAX_ENTRIES = 20u;

	template<typename T>
	class Database
	{
		unsigned int numEntries;
		std::string key[MAX_ENTRIES];
		T value[MAX_ENTRIES];
		std::string dbFileName;

		static std::shared_ptr<Database<T>> instance;

		void encryptDecrypt(T& value) { /* nothing */ };

		Database(const std::string& filename)//Private constructors to prevent instancing
		{
			std::cout << "[" << this << "] " << "Database(const std::string&)\n";
			dbFileName = filename;
			std::ifstream myfile(dbFileName);
			if (myfile.is_open())
			{
				numEntries = 0;
				while (!myfile.eof() && numEntries < MAX_ENTRIES)
				{
					myfile >> key[numEntries];
					myfile >> value[numEntries];
					std::replace(key[numEntries].begin(), key[numEntries].end(), '_', ' ');
					encryptDecrypt(value[numEntries]);
					++numEntries;
				}
				myfile.close();
			}
		}

	public:

		static std::shared_ptr<Database<T>> getInstance(const std::string& dbFileName) {
			if (instance == nullptr) {//if an object of type Database does not yet exist, create one.
				instance = std::shared_ptr<Database<T>>(new Database(dbFileName));//Database will be managed by a shared pointer
			}
			return instance;
		}

		Err_Status GetValue(const std::string& key, T& value) {
			Err_Status status = Err_Status::Err_NotFound;
			for (auto i = 0u; i < numEntries && status == Err_Status::Err_NotFound; ++i) {
				if (key == this->key[i]) {
					value = this->value[i];
					status = Err_Status::Err_Success;
				}
			}
			return status;
		}

		Err_Status SetValue(const std::string& key, const T& value) {
			Err_Status status = Err_Status::Err_OutOfMemory;
			if (numEntries < MAX_ENTRIES) {
				status = Err_Status::Err_Success;
				this->key[numEntries] = key;
				this->value[numEntries] = value;
				++numEntries;
			}
			return status;
		}

		~Database()
		{
			std::cout << "[" << this << "] " << "~Database()\n";
			std::ofstream myfile(dbFileName + ".bkp.txt");
			for (auto i = 0u; i < numEntries; ++i)
			{
				encryptDecrypt(value[i]);
				myfile << std::left << std::setw(25) << key[i]
				       << " -> " << value[i] << std::endl;
			}
			myfile.close();
		}
	};

	template<>
	inline void Database<std::string>::encryptDecrypt(std::string& value)
	{
		const char secret[]{ "secret encryption key" };

		// TODO: encode/decode here
		// See https://kylewbanks.com/blog/Simple-XOR-Encryption-Decryption-in-Cpp
		for (size_t i = 0u; i < value.size(); ++i)
			for (size_t j = 0u; j < sizeof(secret) / sizeof(secret[0]); ++j)
				value[i] = value[i] ^ secret[j];
	}

	template<>
	inline void Database<long long>::encryptDecrypt(long long& value)
	{
		const char secret[]{ "super secret encryption key" };
		char* data = reinterpret_cast<char*>(&value);

		// TODO: encode/decode here
		// See https://kylewbanks.com/blog/Simple-XOR-Encryption-Decryption-in-Cpp
		for (size_t i = 0u; i < sizeof(value); ++i)
			for (size_t j = 0u; j < sizeof(secret) / sizeof(secret[0]); ++j)
				data[i] = data[i] ^ secret[j];
	}

	template<typename T>
	std::shared_ptr<Database<T>> Database<T>::instance{};
}

#endif// SENECA_DATABASE_H
