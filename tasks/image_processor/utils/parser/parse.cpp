#include "utils/parser/parse.h"


InputArgs parse(const int argc, const char** argv) {
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
        if (argv[i][0] == '-') {
            // argument
            if ('0' <= argv[i][1] && argv[i][1] <= '9') {
                if (args.filter_args.empty()) {
                    throw "need to specify the filter name first";
                }
                args.filter_args.back().args.push_back(argv[i]);
            }
            // filter name
            else {
                args.filter_args.push_back((FilterArgs){ 
                    .name=((std::string)argv[i]).substr(1), 
                    .args={} 
                });
            }
        }
    }
    return args;
}
