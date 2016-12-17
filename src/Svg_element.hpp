//
//  Svg_element.hpp
//  SVGRasterizer
//
//  Created by Razvan Pascalau on 07/05/16.
//
//

#pragma once

#include <string>
#include <gsl/string_span>

class Svg_element final {
public:
    explicit Svg_element(const char* name_)
            :name{name_} { }

    Svg_element() = default;

    Svg_element(const Svg_element&) = default;

    Svg_element(Svg_element&&) = default;

    Svg_element& operator=(const Svg_element&) = default;

    Svg_element& operator=(Svg_element&&) = default;

    auto get_name() const -> gsl::cstring_span<> { return gsl::cstring_span<>(name); }

private:
    friend auto operator<(const Svg_element& lhs, const Svg_element& rhs) -> bool;

    friend auto operator<(const Svg_element& lhs, gsl::cstring_span<> rhs) -> bool;

    friend auto operator<(gsl::cstring_span<> lhs, const Svg_element& rhs) -> bool;

    std::string name;
};

inline auto operator<(const Svg_element& lhs, const Svg_element& rhs) -> bool
{
    return lhs.get_name()<rhs.get_name();
}

inline auto operator<(const Svg_element& lhs, gsl::cstring_span<> rhs) -> bool
{
    return lhs.get_name()<rhs;
}

inline auto operator<(gsl::cstring_span<> lhs, const Svg_element& rhs) -> bool
{
    return lhs<rhs.get_name();
}

