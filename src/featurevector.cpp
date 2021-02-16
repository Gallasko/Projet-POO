#include "featurevector.h"

#include <cmath>

FeatureVector::FeatureVector(std::vector<std::string> fVector) : dataVector(fVector)
{
    norme = 0.0f;
    
    for(auto feature : dataVector)
        norme += std::stof(feature) * std::stof(feature);

    norme = std::sqrt(norme);
}