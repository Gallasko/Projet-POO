#pragma once

#include <vector>
#include <string>

#include "featurevector.h"

class Sample
{
public:
    Sample(std::string tag, std::vector<std::string> fVector) : tag(tag), featureVector(fVector) {};

    inline std::string getTag() const { return tag; }
    inline FeatureVector getFeature() const { return featureVector; }

private:
    std::string tag;
    FeatureVector featureVector;
};