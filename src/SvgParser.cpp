//
//  SVGParser.cpp
//  SVGRasterizer
//
//  Created by Razvan Pascalau on 15/01/16.
//  Copyright © 2016 Razvan Pascalau. All rights reserved.
//

#include "SvgParser.h"
#include <iostream>
#include "pugixml/pugixml.hpp"
#include "gsl/gsl"
#include "ConfigLoader.h"


namespace
{
	google::dense_hash_map<uint32_t, std::function<bool(const Config&)>> element_processors;
}

template<typename ElementType>
bool parseRawElement(const ElementType& raw_element, const Config& config)
{
	gsl::cstring_span<> element_name = gsl::ensure_z(raw_element.name());

	return false;
}

bool parseSVG(const std::string& svgFilePath, const std::string& configFilePath)
{
	const auto configuration = ConfigLoader::loadConfigAtPath(configFilePath);
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(svgFilePath.c_str());
	if (result.status != pugi::status_ok)
		return false;
	std::cout << "First node name: [" << doc.first_child().name() << "]\n";

	//start with elements
	std::for_each(std::begin(doc), std::end(doc), [&configuration](const auto& raw_element)
	{
		parseRawElement(raw_element, configuration);
	});

	//    std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << std::endl;
	return false;
}

//template <typename SVGElementType
//bool parseElement(SVGElement )
//{
//	return false;
//}
