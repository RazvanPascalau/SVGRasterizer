//
// Created by Razvan Pascalau on 23/12/2016.
//
#pragma once

#include <functional>
#include <mutex>
#include "gsl/gsl"
#include "Config_reader.hpp"

//template <typename Ele
using Element_processor=const std::function<bool(const Indexed_config&)>; //there are no strings attached on me

auto get_element_processor(const std::string& element_name) -> Element_processor&;
