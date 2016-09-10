//
//  main.cpp
//  SVGRasterizer
//
//  Created by Razvan Pascalau on 13/01/16.
//  Copyright © 2016 Razvan Pascalau. All rights reserved.
//
#define CATCH_CONFIG_RUNNER
#include "Catch/catch.hpp"
#include "SvgParser.h"

TEST_CASE("MainTestCase", "[Main]")
{
}

int main( int argc, char* const argv[] )
{
	// global setup...

	int result = Catch::Session().run( argc, argv );

	// global clean-up...
	const auto path = std::string{ "/Users/razvanpascalau/dev/test.svg" };
	//TODO add a logging framework instead of printf
	if (argc < 2)
	{
		printf("Too few parameters: we need to pass the configuration file as parameter");
		return 1;
	}
	parseSVG(path, argv[1]);
	return result;
}