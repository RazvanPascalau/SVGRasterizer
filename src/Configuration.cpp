//
// Created by Razvan Pascalau on 18/08/16.
//

#include "Configuration.hpp"
#include <cassert>

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
}
