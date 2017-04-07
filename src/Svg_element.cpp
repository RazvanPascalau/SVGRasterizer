//
// Created by Razvan Pascalau on 02/04/2017.
//
#include "Svg_element.hpp"
#include <unordered_map>
#include <experimental/string_view>

namespace {
    using el = Svg_elem_id;
    using Element_name_map = std::unordered_map<std::experimental::string_view, el>;
    const Element_name_map element_name_map{
            {"svg",    el::svg},
            {"circle", el::circle},
            {"g",      el::g}
    };
}

auto Svg_element::get_id_for_name(gsl::not_null<const char*> element_name) -> std::experimental::optional<Svg_elem_id>
{
    auto elem_it = element_name_map.find(element_name.get());
    if(elem_it != std::end(element_name_map))
    {
        return elem_it->second;
    }
    return {};
}
