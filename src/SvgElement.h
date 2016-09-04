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
	friend bool operator<(const SvgElement& lhs, const SvgElement& rhs);
	friend bool operator<(const SvgElement& lhs, const std::string& rhs);
	friend bool operator<(const std::string& lhs, const SvgElement& rhs);
};

inline bool operator<(const SvgElement& lhs, const SvgElement& rhs)
{
	return lhs.name < rhs.name;
}

inline bool operator<(const SvgElement& lhs, const std::string& rhs)
{
	return lhs.name < rhs;
}

inline bool operator<(const std::string& lhs, const SvgElement& rhs)
{
	return lhs < rhs.name;
}
