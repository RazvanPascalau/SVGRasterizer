//
//  SvgElement.hpp
//  SVGRasterizer
//
//  Created by Razvan Pascalau on 07/05/16.
//
//

#pragma once

#include <string>
using SvgElementId = uint32_t;

struct SvgElement
{
	std::string name;
	SvgElementId id;
};