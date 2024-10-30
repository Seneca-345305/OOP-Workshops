// Exercise - STL Containers
// 2021/12/05 - Gideon

#include <fstream>
#include <exception>

#include "Filesystem.h"

namespace seneca {
    std::string Filesystem::_trim(std::string str) {
        str = str.substr(str.find_first_not_of(' '));
        str = str.substr(0, str.find_last_not_of(' ') + 1);
        return str;
    }

    Filesystem::Filesystem(const char* filename, const std::string& root_name) {
        std::ifstream file(filename);

        if (!file) {
            throw std::string("File does not exist!");
        }

        m_root = new Directory(root_name);
        m_current = m_root;

        std::string record;

        while (file) {
            std::getline(file, record);
            std::string path;

            size_t path_terminator = record.find_first_of('|');
            if (path_terminator == std::string::npos) {
                path = _trim(record);
            }
            else {
                path = _trim(record.substr(0, path_terminator));
                record = _trim(record.substr(path_terminator + 1));
            }

            Directory* current = m_root;

            while (!path.empty()) {
                size_t separator = path.find_first_of('/');
                Resource* res;
                if (separator != std::string::npos) {
                    std::string dir_name = path.substr(0, separator) + "/";
                    res = current->find(dir_name);
                    if (!res) {
                        res = new Directory(dir_name);
                        res->update_parent_path(current->path());
                        *current += res;
                    }
                    current = dynamic_cast<Directory*>(res);
                    path.erase(0, separator + 1);
                }
                else {
                    res = new File(path, record);
                    res->update_parent_path(current->path());
                    *current += res;
                    path.erase();
                }
            }
        }
    }

    Filesystem::Filesystem(Filesystem&& src) noexcept {
        *this = std::move(src);
    }

    Filesystem& Filesystem::operator=(Filesystem&& src) noexcept {
        if (this != &src)
        {
            delete m_root;

            m_root = src.m_root;
            m_current = src.m_current;
            src.m_root = nullptr;
            src.m_current = nullptr;
        }
        return *this;
    }

    Filesystem::~Filesystem() {
        delete m_root;
    }

    Filesystem& Filesystem::operator+=(Resource* resource) {
        *m_current += resource;
        return *this;
    }

    Directory* Filesystem::change_directory(const std::string& dir_name) {
        if (dir_name.empty()) {
            m_current = m_root;
            return m_current;
        }

        Resource* dir = m_current->find(dir_name);

        if (!dir) {
            throw std::invalid_argument("Cannot change directory! " + dir_name + " not found!");
        }

        m_current = dynamic_cast<Directory*>(dir);
        return m_current;
    }

    Directory* Filesystem::get_current_directory() const {
        return m_current;
    }
}
