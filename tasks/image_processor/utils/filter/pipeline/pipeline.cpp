#include "utils/filter/pipeline/pipeline.h"
#include "utils/filter/factory/factory.h"


Pipeline::Pipeline(const std::vector<FilterArgs>& args) {
    for (size_t i = 0; i < args.size(); ++i) {
        if (NAME_FILTER_MATCH.find(args[i].name) == NAME_FILTER_MATCH.end()) {
            throw "No such filter " + args[i].name;
        }
        filters.push_back(NAME_FILTER_MATCH.at(args[i].name)(args[i]));
    }
}

Image Pipeline::apply(const Image& image) {
    Image tmp = image;
    for (const std::unique_ptr<Filter>& filter : filters) {
        tmp = filter->apply(tmp);
    }
    return tmp;
}
