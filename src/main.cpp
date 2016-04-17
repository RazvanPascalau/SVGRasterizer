//
//  main.cpp
//  SVGRasterizer
//
//  Created by Razvan Pascalau on 13/01/16.
//  Copyright © 2016 Razvan Pascalau. All rights reserved.
//
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "SVGParser.hpp"
#include "Catch/catch.hpp"

TEST_CASE("basic enum bitmask usage", "[EnumBitMask]")
{
    const auto path = std::string{ "/Users/razvanpascalau/dev/test.svg" };
    parseSVG(path);
}
