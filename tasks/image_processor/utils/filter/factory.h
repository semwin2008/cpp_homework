#pragma once

#include <unordered_map>
#include <functional>
#include "crop/crop.h"
#include "grayscale/grayscale.h"
#include "negative/negative.h"
#include "sharpening/sharpening.h"
#include "edgeDetection/edgeDetection.h"
#include "gaussianBlur/gaussianBlur.h"
#include "elasticTransform/elasticTransform.h"


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
