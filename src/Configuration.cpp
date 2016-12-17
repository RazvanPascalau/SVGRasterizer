//
// Created by Razvan Pascalau on 18/08/16.
//

#include "Configuration.hpp"

namespace configuration {
    Raw::Raw(Raw::Element_container_type&& elements_, Raw::Element_group_type&& groups_,
            Raw::Children_map_type&& children_)
            :elements(elements_), groups(groups_), children(children_)
    {
    }

    Indexed::Indexed(Raw&& raw_config_)
            :raw_config(raw_config_) //move op
    {
    }

    auto Indexed::get_raw_config() const -> const Raw&
    {
        return raw_config;
    }

    auto Indexed::get_index_of_element(gsl::cstring_span<> name) const -> Indexed::Element_index_type
    {
        Indexed::Element_index_type index_of_name = std::numeric_limits<Indexed::Element_index_type>::max();
        const auto& all_elements = raw_config.elements;
        uint32_t index_for_name{std::numeric_limits<uint32_t>::max()};
        assert(std::is_sorted(std::begin(all_elements), std::end(all_elements)));
        //@TODO: check if this is correct
        auto searched_name_it = std::lower_bound(std::begin(all_elements), std::end(all_elements),
                name);
        while (searched_name_it!=all_elements.end() && searched_name_it->get_name()!=name)
            ++searched_name_it;

        if (searched_name_it!=all_elements.end() && searched_name_it->get_name()==name) {
            index_of_name = std::distance(all_elements.begin(), searched_name_it);
        }
        return index_of_name;
    }

    auto Indexed::get_index_of_element(const std::string& name) const -> Indexed::Element_index_type
    {
        const gsl::cstring_span<> name_span = name;
        return get_index_of_element(name_span);
    }

}
