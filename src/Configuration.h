//
// Created by Razvan Pascalau on 18/08/16.
//
#pragma once

#include <vector>
#include <string>
#include <sparsehash/dense_hash_map>
#include <gsl/string_span>
#include "Svg_element.h"

namespace configuration {
    struct Raw {
        using Element_container_type = std::vector<Svg_element>;
        using Children_map_type = google::dense_hash_map<std::string, std::vector<std::string>>;
        using Element_group_type =  google::dense_hash_map<std::string, std::vector<std::string>>;

        Raw() = default;

        Raw(Raw&&) = default;

        Raw(const Raw&) = default;

        Raw(Element_container_type&& elements_, Element_group_type&& groups_,
                Children_map_type&& children_);

        const Element_container_type elements;
        const Element_group_type groups;
        const Children_map_type children;
    };

    class Indexed {
        using Element_index_type = uint32_t;
    public:
        Indexed() = default;

        Indexed(Raw&&);

        Indexed(const Indexed&) = default;

        Indexed(Indexed&&) = default;

        Indexed& operator=(const Indexed&) = default;

        Indexed& operator=(Indexed&&) = default;

        ~Indexed() = default;

        Element_index_type get_index_of_element(const std::string& name) const;
        const Raw& get_raw_config() const;

    private:
        const Raw raw_config;
    };
}
using Raw_config = configuration::Raw;
using Indexed_config = configuration::Indexed;
