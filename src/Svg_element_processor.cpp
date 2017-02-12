//
// Created by Razvan Pascalau on 23/12/2016.
//

#include "Svg_element_processor.hpp"

//parsing functions
bool parse_svg(const Indexed_config&);
bool parse_g(const Indexed_config&);
bool parse_circle(const Indexed_config&);

namespace element_name {
    const std::string svg  {"svg"};
    const std::string g {"g"};
    const std::string circle {"circle"};
}

class Element_processor_map final
{

};
namespace internal {
    using Element_processor_map= std::unordered_map<std::string, Element_processor>;
    namespace el = element_name;

    const Element_processor_map elem_processor_map {
            {el::svg, &parse_svg},
            {el::g, &parse_g},
            {el::circle, &parse_circle}
    };
}

auto get_element_processor(const std::string& element_name) -> Element_processor&
{
    auto& processor_map = internal::elem_processor_map;
    auto processor_it = processor_map.find(element_name);
    if (processor_it==std::end(processor_map)) {
        //TODO: add configuration option to ignore unknown elements
        throw "This element is unknown";
    }
    return processor_it->second;
}

bool parse_svg(const Indexed_config&)
{
    throw "parseSvg: This needs to be implemented";
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
