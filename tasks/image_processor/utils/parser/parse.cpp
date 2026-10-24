#include "parse.h"
#include <iostream>


InputArgs parse(int argc, char** argv) {
    InputArgs args;
    if (argc == 2) {
        throw "Need to specify input file";
    }
    args.input_file_path = argv[1];
    if (argc == 3) {
        throw "Need to specify output file";
    }
    args.output_file_path = argv[2];
    for (int i = 3; i < argc; ++i) {
        if (argv[i] == "") {
            throw "Argument or filter name cannot be empty";
        }
        if (argv[i] == "-") {
            throw "Filter name cannot be empty";
        }
        // filter name
        if (argv[i][0] == '-') {
            args.filter_args.emplace_back(((std::string)argv[i]).substr(1), FilterArgs{});
        }else{
            // argument
            if (args.filter_args.empty()) {
                throw "need to specify the filter name first";
            }
            args.filter_args.back().second.push_back(argv[i]);
        }
    }
    return args;
}
