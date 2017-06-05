//
// Created by Razvan Pascalau on 01/05/2017.
//

#define CATCH_CONFIG_MAIN

#include "../include/SVGRasterizer/Svg_parser.hpp"
#include "catch.hpp"
#include "spdlog/spdlog.h"

TEST_CASE("MainTestCase", "[Main]")
{
    const auto testFilePath = std::string{"/Users/razvanpascalau/dev/SVGRasterizer/test.svg"};
    const auto configurationFilePath = std::string{"/Users/razvanpascalau/dev/SVGRasterizer/configuration.json"};
    parse_svg_file(testFilePath, configurationFilePath);
}
