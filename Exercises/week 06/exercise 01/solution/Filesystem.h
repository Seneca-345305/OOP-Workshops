// Exercise - STL Containers

#ifndef SENECA_FILESYSTEM_H
#define SENECA_FILESYSTEM_H

#include <vector>
#include <ostream>

#include "Resource.h"
#include "Directory.h"
#include "File.h"
#include "Flags.h"

namespace seneca {
    class Filesystem {
        Directory* m_root = nullptr;
        Directory* m_current = nullptr;

        std::string _trim(std::string);

    public:
        Filesystem(const char*, const std::string & = "");
        Filesystem(const Filesystem&) = delete;
        Filesystem& operator=(const Filesystem&) = delete;
        Filesystem(Filesystem&&) noexcept;
        Filesystem& operator=(Filesystem&&) noexcept;
        ~Filesystem();

        Filesystem& operator+=(Resource*);
        Directory* change_directory(const std::string & = "");
        Directory* get_current_directory() const;
    };
}

#endif
