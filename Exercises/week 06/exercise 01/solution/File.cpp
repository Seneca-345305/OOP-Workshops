// Exercise - STL Containers

#include <iomanip>
#include <ostream>
#include <string>

#include "Flags.h"
#include "File.h"


namespace seneca {
    File::File(const std::string& name, const std::string& contents) : m_contents(contents) {
        m_name = name;
    }

    void File::update_parent_path(const std::string& parent_path) {
        m_parent_path = parent_path;
    }

    NodeType File::type() const {
        return NodeType::FILE;
    }

    std::string File::path() const {
        return m_parent_path + m_name;
    }

    std::string File::name() const {
        return m_name;
    }

    int File::count() const {
        return -1;
    }

    size_t File::size() const {
        return m_contents.length();
    }
}  // namespace seneca
