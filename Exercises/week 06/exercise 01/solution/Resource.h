// Exercise - STL Containers

#ifndef SENECA_RESOURCE_H
#define SENECA_RESOURCE_H

#include <iostream>
#include <string>
#include "Flags.h"

namespace seneca {
    class Resource {
    protected:
        // Stores the name of the resource
        std::string m_name{};
        // Stores the absolute path of the folder where the resource is located
        std::string m_parent_path = "/";

    public:
        virtual void update_parent_path(const std::string&) = 0;
        virtual std::string name() const = 0;
        virtual int count() const = 0;
        virtual std::string path() const = 0;
        virtual size_t size() const = 0;
        virtual NodeType type() const = 0;
        virtual ~Resource() = default;
    };
}  // namespace seneca

#endif
