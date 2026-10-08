#pragma once

#include "utils/args/filterArgs.h"
#include <string>


class InputArgs{
public:
    FilterArgs getFilterArgs();
    std::string getInputFilePath();
    std::string getOutputFilePath();

private:
    FilterArgs filter_args;
    std::string input_file_path;
    std::string output_file_path;
};