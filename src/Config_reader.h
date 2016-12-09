//
// Created by Razvan Pascalau on 16/08/16.
//
#pragma once

#include <Configuration.h>

namespace configuration {
    namespace reader {
        Raw_config readRawConfigAtPath(const std::string& config_path);

        Indexed_config readIndexedConfigAtPath(const std::string& config_path);
    }
};