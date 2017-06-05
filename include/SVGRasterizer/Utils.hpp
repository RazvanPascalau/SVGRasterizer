//
// Created by Razvan Pascalau on 11/12/2016.
//
#pragma once

#include <limits>
#include <stdbool.h>

namespace utils
{
    //@ TODO: restrict the type to integral types, int, short, byte, etc.
    template <typename IntegralType>
    inline bool is_index_valid(const IntegralType index)
    {
        return index < std::numeric_limits<IntegralType>::max();
    }
}