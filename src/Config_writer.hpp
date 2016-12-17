//
// Created by Razvan Pascalau on 04/12/2016.
//
#pragma once
#include <string>
#include "Configuration.hpp"

namespace configuration {
    namespace writer {
        auto write_to_file(const Raw_config& raw_config, const std::string& out_file_path) -> void;
    }
};
