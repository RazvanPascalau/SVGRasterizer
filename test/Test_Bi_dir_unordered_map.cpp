//
// Created by Razvan Pascalau on 01/05/2017.
//

#include "catch.hpp"
#include "SVGRasterizer/Bi_dir_unordered_map.hpp"

TEST_CASE("Bi_directional_unordered_map", "[Bi_dir_unordered_map]")
{
    Bi_dir_unordered_map<int,float> my_map {{1, 2.9},{3,6.7}};
    Bi_dir_unordered_map<int,int> map2 { {1,1}, {3,2}};

    auto result = my_map.get<int>(1.0f);
}
