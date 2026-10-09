#pragma once

#include "utils/args/filterArgs.h"
#include <string>


struct InputArgs{
    std::vector<FilterArgs> filter_args;
    std::string input_file_path;
    std::string output_file_path;
};