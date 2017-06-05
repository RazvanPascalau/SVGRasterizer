//
// Created by Razvan Pascalau on 07/04/2017.
//  Bidirectional unordered map which is basically a class that has two unordered_maps
#pragma once

#include <unordered_map>

template<typename FirstType, typename SecondType>
class Bi_dir_unordered_map {

public:
    constexpr Bi_dir_unordered_map()
    {
    }

    constexpr Bi_dir_unordered_map(std::initializer_list<std::pair<const FirstType, SecondType>> il)
            :
            map(il)
    {
        for (const auto& map_element: il) {
            reversed_map.emplace(std::make_pair(map_element.second, map_element.first));
        }
    }

    template<typename U = SecondType,
            typename T = FirstType,
            typename = std::enable_if_t<std::is_same<U, SecondType>::value>,
            typename = std::enable_if_t<std::is_same<T, FirstType>::value>>
    constexpr auto get(const T& key) -> std::enable_if_t<!std::is_same<T, U>::value, const U&>
    {
        return map[key];
    };

    template<typename T = FirstType,
            typename U = SecondType,
            typename = std::enable_if_t<std::is_same<U, SecondType>::value>,
            typename = std::enable_if_t<std::is_same<T, FirstType>::value>>
    constexpr auto get(const U& key) -> std::enable_if_t<!std::is_same<T, U>::value, const T&>
    {
        return reversed_map[key];
    };

    constexpr auto get_with_first(const FirstType& key) -> const SecondType&
    {
        return map[key];
    }

    constexpr auto get_with_second(const SecondType& key) -> const FirstType&
    {
        return reversed_map[key];
    }

private:
    typename std::unordered_map<FirstType, SecondType> map;
    typename std::unordered_map<SecondType, FirstType> reversed_map;
};
