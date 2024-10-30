// Exercise - STL Containers
// 2021/12/05 - Gideon

#ifndef SENECA_DIRECTORY_H
#define SENECA_DIRECTORY_H

#include <vector>
#include <forward_list>

#include "Flags.h"
#include "Resource.h"

namespace seneca {
    class Directory : public Resource {
        std::vector<Resource*> m_contents;

        template<typename T>
        bool has_flag_set(std::vector<T>, T) const;

    public:

        Directory(const std::string&);
        ~Directory();
        Directory& operator+=(Resource*);
        Resource* find(const std::string&, const std::vector<OpFlags>& = {});

        void update_parent_path(const std::string&) override;
        NodeType type() const override;
        std::string path() const override;
        std::string name() const override;
        size_t size() const override;
        int count() const override;

        void remove(const std::string&, const std::vector<OpFlags>& = {});
        void display(std::ostream&, const std::vector<FormatFlags>& = {}) const;
    };
}  // namespace seneca

#endif
