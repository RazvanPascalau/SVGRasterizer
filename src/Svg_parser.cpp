//
//  SVGParser.cpp
//  SVGRasterizer
//
//  Created by Razvan Pascalau on 15/01/16.
//  Copyright © 2016 Razvan Pascalau. All rights reserved.
//

#include "Svg_parser.hpp"
#include <iostream>
#include "pugixml/pugixml.hpp"
#include "Config_reader.hpp"
#include "Config_writer.hpp"
#include "Utils.hpp"
#include "Svg_element_processor.hpp"

auto parse_raw_attribute(const pugi::xml_attribute& raw_attribute, const Indexed_config& config) -> bool
{

    return false;
}

auto parse_raw_element(const pugi::xml_node& raw_element, const Indexed_config& config) -> bool
{
    std::string element_name = raw_element.name();

    auto index = config.get_index_of_element(element_name);
    //@TODO: replace this workaround with optional/structured bindings from C++17
    if (!utils::is_index_valid(index))
        return false;
    auto& elem_processor = get_element_processor(element_name);
    const auto& raw_attributes = raw_element.attributes();
    for(const auto& single_attribute : raw_attributes)
    {
        parse_raw_attribute(single_attribute, config);
    }
    bool success = elem_processor(config);
    return success;
}


auto parse_svg_file(const std::string& svg_file_path, const std::string& config_file_path) -> bool
{
    const auto configuration = configuration::reader::readIndexedConfigAtPath(config_file_path);
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(svg_file_path.c_str());
    if (result.status!=pugi::status_ok)
        return false;
    std::cout << "First node name: [" << doc.first_child().name() << "]\n";

    //start with elements
    std::for_each(std::begin(doc), std::end(doc), [&configuration](const auto& raw_element) {
        parse_raw_element(raw_element, configuration);
    });

    //@TODO: remove this
    configuration::writer::write_to_file(configuration.get_raw_config(),
            "/Users/razvanpascalau/dev/SVGRasterizer/configuration_out.json");
    //    std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << std::endl;
    return false;
}

//template <typename SVGElementType
//bool parseElement(SVGElement )
//{
//	return false;
//}
