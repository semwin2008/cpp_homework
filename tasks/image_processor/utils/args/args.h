#pragma once

#include <string>
#include <vector>


#define FilterArgs std::vector<std::string>

struct InputArgs{
    std::vector<std::pair<std::string, FilterArgs>> filter_args;
    std::string input_file_path;
    std::string output_file_path;
};