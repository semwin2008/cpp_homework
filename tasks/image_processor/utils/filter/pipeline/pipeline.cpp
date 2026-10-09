#include "pipeline.h"
#include <unordered_map>
#include <functional>
#include "utils/filter/crop/crop.h"


// Factory
const std::unordered_map<const std::string, 
std::function<std::unique_ptr<Filter>(const FilterArgs&)>> NAME_FILTER_MATCH = {
    {"crop", cropFactory}
};


Pipeline::Pipeline(const std::vector<FilterArgs>& args) {
    for (size_t i = 0; i < args.size(); ++i) {
        if (NAME_FILTER_MATCH.find(args[i].name) == NAME_FILTER_MATCH.end()) {
            throw "No such filter " + args[i].name;
        }
        filters.push_back(NAME_FILTER_MATCH[args[i].name](args[i].args));
    }
}

Image Pipeline::apply(const Image& image) {
    Image tmp = image;
    for (const std::unique_ptr<Filter>& filter : filters) {
        tmp = filter->apply(tmp);
    }
    return tmp;
}
