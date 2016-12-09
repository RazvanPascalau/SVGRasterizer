//
//  Svg_element.hpp
//  SVGRasterizer
//
//  Created by Razvan Pascalau on 07/05/16.
//
//

#pragma once

#include <string>

struct Svg_element {
    std::string name;

    friend bool operator<(const Svg_element& lhs, const Svg_element& rhs);

    friend bool operator<(const Svg_element& lhs, const std::string& rhs);

    friend bool operator<(const std::string& lhs, const Svg_element& rhs);
};

inline bool operator<(const Svg_element& lhs, const Svg_element& rhs)
{
    return lhs.name<rhs.name;
}

inline bool operator<(const Svg_element& lhs, const std::string& rhs)
{
    return lhs.name<rhs;
}

inline bool operator<(const std::string& lhs, const Svg_element& rhs)
{
    return lhs<rhs.name;
}

