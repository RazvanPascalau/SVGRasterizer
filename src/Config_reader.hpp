//
// Created by Razvan Pascalau on 16/08/16.
//
#pragma once

#include <Configuration.hpp>

namespace configuration {
    namespace reader {
        auto readRawConfigAtPath(const std::string& config_path) -> Raw_config;

        auto readIndexedConfigAtPath(const std::string& config_path) -> Indexed_config;
    }
};