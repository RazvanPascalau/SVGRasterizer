//
//  Svg_element.hpp
//  SVGRasterizer
//
//  Created by Razvan Pascalau on 07/05/16.
//
//

#pragma once

#include <string>
#include <gsl/gsl>
#include <experimental/optional>
#include <experimental/string_view>

enum class Svg_elem_id {
    svg,
    g,
    circle
};

class Svg_element final {
public:
    Svg_element(const char* name_, const Svg_elem_id id_)
            :name{name_},
             id(id_) { }

    Svg_element(const Svg_element&) = default;

    Svg_element(Svg_element&&) = default;

    Svg_element& operator=(const Svg_element& rhs) = default;

    Svg_element& operator=(Svg_element&&) = default;

    auto get_name() const -> const std::string& { return name; }

    auto get_id() const -> const Svg_elem_id { return id; };

    //not a simple getter, will do a lookup and it might fail hence the optional
    static auto get_id_for_name(gsl::not_null<const char*> element_name) -> std::experimental::optional<Svg_elem_id>;

private:
    friend auto swap(Svg_element& lhs, Svg_element& rhs) -> void;

    friend auto operator<(const Svg_element& lhs, const Svg_element& rhs) -> bool;

    friend auto operator<(const Svg_element& lhs, const std::string& rhs) -> bool;

    friend auto operator<(const std::string& lhs, const Svg_element& rhs) -> bool;

    std::string name;
    Svg_elem_id id;
};

inline auto operator<(const Svg_element& lhs, const Svg_element& rhs) -> bool
{
    return lhs.get_name()<rhs.get_name();
}

inline auto operator<(const Svg_element& lhs, const std::string& rhs) -> bool
{
    return lhs.get_name()<rhs;
}

inline auto operator<(const std::string& lhs, const Svg_element& rhs) -> bool
{
    return lhs<rhs.get_name();
}

inline auto swap(Svg_element& lhs, Svg_element& rhs) -> void
{
    using std::swap; // bring in swap for built-in types
}
