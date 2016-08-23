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

bool parseSVG(const std::string &svgFilePath, const std::string& configFilePath) {
	const auto configuration = ConfigLoader::loadConfigAtPath(configFilePath);


	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(svgFilePath.c_str());

	if (result.status != pugi::status_ok)
		return false;
	std::cout << "First node name: [" << doc.first_child().name() << "]\n";

	//    std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << std::endl;
	return false;
}

//template <typename SVGElementType
//bool parseElement(SVGElement )
//{
//	return false;
//}
