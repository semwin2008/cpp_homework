#pragma once

#include "/home/vboxuser/my_hw/ami-Vinogradov-Semion-semwin2008/tasks/image_processor/utils/args/filterArgs.h"
#include <string>
#include <vector>


struct InputArgs{
    std::vector<FilterArgs> filter_args;
    std::string input_file_path;
    std::string output_file_path;
};