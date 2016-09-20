//
//  SvgElement.hpp
//  SVGRasterizer
//
//  Created by Razvan Pascalau on 07/05/16.
//
//

#pragma once

#include <string>

struct SvgElement
{
	std::string name;
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

