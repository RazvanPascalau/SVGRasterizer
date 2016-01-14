//
//  SVGParser.cpp
//  SVGRasterizer
//
//  Created by Razvan Pascalau on 15/01/16.
//  Copyright © 2016 Razvan Pascalau. All rights reserved.
//

#include "SVGParser.hpp"
#include "pugixml.hpp"
#include <iostream>

bool parseSVG(const std::string& filePath)
{
    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file(filePath.c_str());

    //    std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << std::endl;
    return false;
}
