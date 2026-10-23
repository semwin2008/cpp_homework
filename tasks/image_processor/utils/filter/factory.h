#pragma once

#include <unordered_map>
#include <functional>
#include "utils/filter/crop/crop.h"
#include "utils/filter/grayscale/grayscale.h"
#include "utils/filter/negative/negative.h"
#include "utils/filter/sharpening/sharpening.h"
#include "utils/filter/edgeDetection/edgeDetection.h"
#include "utils/filter/gaussianBlur/gaussianBlur.h"
#include "utils/filter/elasticTransform/elasticTransform.h"


template<class Filt>
std::unique_ptr<Filter> Factory(const FilterArgs& args) {
    return std::make_unique<Filt>(args);
}

const std::unordered_map<std::string, 
std::function<std::unique_ptr<Filter>(const FilterArgs&)>> NAME_FILTER_MATCH = {
    {"crop", Factory<Crop>},
    {"gs", Factory<Grayscale>},
    {"neg", Factory<Negative>},
    {"sharp", Factory<Sharpening>},
    {"edge", Factory<EdgeDetection>},
    {"blur", Factory<GaussianBlur>},
    {"elastic", Factory<ElasticTransform>},
};
