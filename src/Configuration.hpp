//
// Created by Razvan Pascalau on 18/08/16.
//
#pragma once

#include <vector>
#include <string>
#include <gsl/string_span>
#include <unordered_map>
#include "Svg_element.hpp"

namespace configuration {
    struct Raw final {
        using Element_container_type = std::vector<Svg_element>;
        using Children_map_type = std::unordered_map<std::string, std::vector<std::string>>;
        using Element_group_type =  std::unordered_map<std::string, std::vector<std::string>>;

        Raw() = default;

        Raw(Raw&&) = default;

        Raw(const Raw&) = default;

        Raw(Element_container_type&& elements_, Element_group_type&& groups_,
                Children_map_type&& children_);

        const Element_container_type elements;
        const Element_group_type groups;
        const Children_map_type children;
    };

    class Indexed final {
        using Element_index_type = uint32_t;
    public:
        Indexed() = default;

        Indexed(Raw&&);

        Indexed(const Indexed&) = default;

        Indexed(Indexed&&) = default;

        Indexed& operator=(const Indexed&) = default;

        Indexed& operator=(Indexed&&) = default;

        ~Indexed() = default;

        //if not found return largest integral the type can represent
        auto get_index_of_element(const std::string& name) const -> Element_index_type;

        auto get_raw_config() const -> const Raw&;

    private:
        const Raw raw_config;
    };
}
using Raw_config = configuration::Raw;
using Indexed_config = configuration::Indexed;
