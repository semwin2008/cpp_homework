#include "utils/parser/parse.h"
#include "utils/bmp/reader.h"
#include "utils/bmp/writer.h"
#include "utils/filter/pipeline/pipeline.h"
#include "utils/image/image.h"


int main(int argc, char** argv) {
    InputArgs input_args = parse(argc, argv);
    Pipeline pipeline(input_args.filter_args);
    Image image = BMP::read(input_args.input_file_path);
    Image edited_image = pipeline.apply(image);
    BMP::write(input_args.output_file_path, edited_image);
    return 0;
}
