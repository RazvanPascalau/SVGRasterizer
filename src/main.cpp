//
//  main.cpp
//  SVGRasterizer
//
//  Created by Razvan Pascalau on 13/01/16.
//  Copyright © 2016 Razvan Pascalau. All rights reserved.
//
#define CATCH_CONFIG_RUNNER

#include "Svg_parser.hpp"
#include "Catch/catch.hpp"
#include "spdlog/spdlog.h"

TEST_CASE("MainTestCase", "[Main]")
{
}

int main(int argc, char* const argv[])
{
    try {
        auto console = spdlog::stdout_color_mt("console");
        console->info("Entering main!");

        // global setup...
        int result = Catch::Session().run(argc, argv);

        // global clean-up...
        const auto testFilePath = std::string{"/Users/razvanpascalau/dev/test.svg"};
        const auto configurationFilePath = std::string{"/Users/razvanpascalau/dev/SVGRasterizer/configuration.json"};
        parse_svg_file(testFilePath, configurationFilePath);
        return result;
    }
    catch (const spdlog::spdlog_ex& ex) {
        std::cout << "Log failed: " << ex.what() << std::endl;
    }
}