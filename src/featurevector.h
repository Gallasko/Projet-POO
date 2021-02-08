#pragma once

#include <string>
#include <vector>

class FeatureVector
{
public:
    FeatureVector(std::vector<std::string> fVector) : dataVector(fVector) {};

    inline unsigned int size() const { return dataVector.size(); };

    inline std::string operator[](int nb) const { return dataVector[nb]; } 
private:
    std::vector<std::string> dataVector; 
};