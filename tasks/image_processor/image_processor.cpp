#include "utils/parser/parse.h"
#include "utils/bmp/reader.h"
#include "utils/bmp/writer.h"
#include "utils/filter/pipeline/pipeline.h"
#include "utils/image/image.h"
#include "utils/args/args.h"
#include <iostream>


int main(int argc, char** argv) {
    try{
        InputArgs input_args = parse(argc, argv);
        Image image = BMP::read(input_args.input_file_path);
        Pipeline pipeline(input_args.filter_args);
        pipeline.apply(image);
        BMP::write(input_args.output_file_path, image);
        return 0;
    } catch (const std::exception& a) {
        std::cerr << a.what() << std::endl;
        return 1;
    }
}
