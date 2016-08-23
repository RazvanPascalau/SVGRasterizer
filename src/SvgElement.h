//
//  SvgElement.hpp
//  SVGRasterizer
//
//  Created by Razvan Pascalau on 07/05/16.
//
//

#pragma once

#include <string>
using SvgElementId = uint32_t; //TODO: check if this is needed anymore

struct SvgElement
{
	std::string name;
	//	SvgElementId id; //TODO: check if this is needed anymore
};