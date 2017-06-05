//
// Created by Razvan Pascalau on 23/12/2016.
//

#include "Svg_element_processor.hpp"

//parsing functions
bool parse_svg(const Indexed_config&);

bool parse_g(const Indexed_config&);

bool parse_circle(const Indexed_config&);

namespace internal {
    using Element_processor_map= std::unordered_map<Svg_elem_id, Element_processor>;

    const Element_processor_map elem_processor_map{
            {Svg_elem_id::svg,    &parse_svg},
            {Svg_elem_id::g,      &parse_g},
            {Svg_elem_id::circle, &parse_circle}
    };
}

auto get_element_processor(Svg_elem_id element_id) -> Element_processor&
{
    auto& processor_map = internal::elem_processor_map;

    auto processor_it = processor_map.find(element_id);
    if (processor_it==std::end(processor_map)) {
        //TODO: add configuration option to ignore unknown elements
        throw "This element is unknown";
    }
    return processor_it->second;
}

bool parse_svg(const Indexed_config&)
{
    //TODO: implement this
    return false;
}

bool parse_g(const Indexed_config&)
{
    throw "parse_g: This needs to be implemented";
    return false;
}

bool parse_circle(const Indexed_config&)
{
    throw "parse_circle: This needs to be implemented";
    return false;
}
