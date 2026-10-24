#include "pipeline.h"
#include "../factory.h"


Pipeline::Pipeline(const std::vector<std::pair<std::string, FilterArgs>>& args) {
    for (auto [filter_name, filter_args] : args) {
        if (NAME_FILTER_MATCH.find(filter_name) == NAME_FILTER_MATCH.end()) {
            throw std::runtime_error("No such filter " + filter_name);
        }
        filters_.push_back(NAME_FILTER_MATCH.at(filter_name)(filter_args));
    }
}

void Pipeline::apply(Image& image) {
    Image tmp = image;
    for (const std::unique_ptr<Filter>& filter : filters_) {
        filter->apply(tmp);
    }
}
