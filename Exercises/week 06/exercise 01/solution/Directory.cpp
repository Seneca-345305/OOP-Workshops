// Exercise - STL Containers

#include <forward_list>
#include <iomanip>
#include <ostream>
#include <string>
#include <vector>
#include <exception>
#include "Directory.h"
#include "File.h"


namespace seneca {
    template <typename T>
    bool Directory::has_flag_set(std::vector<T> flags, T flag) const {
        for (auto f : flags) {
            if (flag == f) {
                return true;
            }
        }
        return false;
    }

    Directory::Directory(const std::string& name) {
        m_name = name;
    }

    Directory::~Directory()
    {
        while (!m_contents.empty())
        {
            delete m_contents.back();
            m_contents.pop_back();
        }
    }

    void Directory::update_parent_path(const std::string& parent_path) {
        m_parent_path = parent_path;

        for (auto it = m_contents.begin(); it != m_contents.end(); it++) {
            (*it)->update_parent_path(this->path());
        }
    }

    NodeType Directory::type() const {
        return NodeType::DIR;
    }

    std::string Directory::path() const {
        return m_parent_path + name();
    }

    std::string Directory::name() const {
        return m_name;
    }

    int Directory::count() const {
        return m_contents.size();
    }

    size_t Directory::size() const {
        size_t s = 0u;

        for (auto it = m_contents.begin(); it != m_contents.end(); it++) {
            s += (*it)->size();
        }

        return s;
    }

    Directory& Directory::operator+=(Resource* resource) {
        for (Resource* r : m_contents) {
            std::string r_name = r->name();

            if (r_name == resource->name()) {
                throw std::string("Resource already exists in directory!");
            }
        }

        m_contents.push_back(resource);
        resource->update_parent_path(path());

        return *this;
    }

    Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags) {
        bool recursive = has_flag_set(flags, OpFlags::RECURSIVE);

        for (auto it = m_contents.cbegin(); it != m_contents.cend(); it++) {
            std::string n = (*it)->name();
            if (name == n)
                return *it;

            if ((*it)->type() == NodeType::DIR && recursive) {
                Resource* res = dynamic_cast<Directory*>(*it)->find(name, flags);
                if (res)
                    return res;
            }
        }

        return nullptr;
    }

    void Directory::remove(const std::string& rname, const std::vector<OpFlags>& flags) {
        bool recursive = has_flag_set(flags, OpFlags::RECURSIVE);

        std::vector<Resource*>::iterator it;
        Resource* resource = nullptr;

        for (it = m_contents.begin(); it != m_contents.end() && !resource; it++) {
            std::string n = (*it)->name();
            if (n == rname)
            {
                resource = *it;
            }
        }

        if (!resource) {
            throw std::invalid_argument(rname + " does not exist in " + name());
        }

        if (resource->type() == NodeType::DIR && !recursive) {
            throw std::string(rname + " is a directory. Pass the recursive flag to delete directories.");
        }

        it--;
        m_contents.erase(it);
        delete resource;
    }

    void Directory::display(std::ostream& os, const std::vector<FormatFlags>& flags) const {
        bool long_form = has_flag_set(flags, FormatFlags::LONG);

        os << "Total size: " << size() << " bytes" << std::endl;

        for (Resource* r : m_contents)
        {
            os << (r->type() == NodeType::FILE ? "F | " : "D | ")
                << std::setw(15) << std::left << r->name() << " |";

            if (long_form)
            {
                int c = r->count();
                os << " "
                    << std::setw(2) << std::right << (c < 0 ? "" : std::to_string(c))
                    << " | "
                    << std::setw(10) << std::to_string(r->size()) + " bytes" << " | ";
            }

            os << std::right << std::endl;
        }
    }
}  // namespace seneca
