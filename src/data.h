#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "sample.h"

class Data
{
public:
    Data();

    inline std::vector<Sample> getData() const { return data; }
    void load(std::string path);

    inline unsigned int getNbSamples() const { return nbSamples; }

    Sample operator[](int nb) { try { return data[nb]; } catch (...) { throw; } }

private:
    std::vector<Sample> data;
    unsigned int nbSamples = 0;
    unsigned int nbFeatures = 0;
};