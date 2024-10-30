// Exercise - STL Containers
// 2021/12/05 - Gideon

#ifndef SENECA_FILE_H
#define SENECA_FILE_H

#include <string>
#include <ostream>

#include "Resource.h"

namespace seneca {
    class File : public Resource {
        std::string m_contents;

    public:
        File(const std::string&, const std::string & = "");
        void update_parent_path(const std::string&);
        NodeType type() const;
        std::string path() const;
        std::string name() const;
        int count() const;
        size_t size() const;
    };
}  // namespace seneca

#endif
