#pragma once

#include <string>
#include <vector>

class FeatureVector
{
public:
    FeatureVector(std::vector<std::string> fVector);

    inline unsigned int size() const { return dataVector.size(); }
    inline float getNorme() const { return norme; }

    inline std::string operator[](int nb) const { return dataVector.at(nb); }
    inline bool operator==(const FeatureVector& rhs) const { if(size() != rhs.size()) return false; bool res = true; for(int i = 0; i < size(); i++) res &= dataVector[i] == rhs[i]; return res;}
    
private:
    std::vector<std::string> dataVector; 
    float norme;
};