//
//  main.cpp
//  SVGRasterizer
//
//  Created by Razvan Pascalau on 13/01/16.
//  Copyright © 2016 Razvan Pascalau. All rights reserved.
//
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "SvgParser.h"
#include "Catch/catch.hpp"

TEST_CASE("MainTestCase", "[Main]")
{
    const auto path = std::string{ "/Users/razvanpascalau/dev/test.svg" };
    parseSVG(path);
}
