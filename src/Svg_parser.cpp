//
//  SVGParser.cpp
//  SVGRasterizer
//
//  Created by Razvan Pascalau on 15/01/16.
//  Copyright © 2016 Razvan Pascalau. All rights reserved.
//

#include "Svg_parser.h"
#include <iostream>
#include "pugixml/pugixml.hpp"
#include "gsl/gsl"
#include "Config_reader.h"
#include "Config_writer.h"

template<typename ElementType>
bool parseRawElement(const ElementType& raw_element, const Indexed_config& config)
{
    auto element_name = gsl::ensure_z(raw_element.name());

    return false;
}

bool parse_svg_file(const std::string& svg_file_path, const std::string& config_file_path)
{
    const auto configuration = configuration::reader::readIndexedConfigAtPath(config_file_path);
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(svg_file_path.c_str());
    if (result.status!=pugi::status_ok)
        return false;
    std::cout << "First node name: [" << doc.first_child().name() << "]\n";

    //start with elements
    std::for_each(std::begin(doc), std::end(doc), [&configuration](const auto& raw_element) {
        parseRawElement(raw_element, configuration);
    });

    //@TODO: remove this
    configuration::writer::write_to_file(configuration.get_raw_config(), "/Users/razvanpascalau/dev/SVGRasterizer/configuration_out.json");
    //    std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << std::endl;
    return false;
}

//template <typename SVGElementType
//bool parseElement(SVGElement )
//{
//	return false;
//}
