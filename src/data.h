#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "sample.h"

class Data
{
public:
    Data() : nbSamples(0), nbFeatures(0) {};

    inline std::vector<Sample> getData() const { return data; }
    void load(std::string path);
    
    Data split(int pos);
    Data split(float percentage);

    void append(Data data);

    inline unsigned int getNbSamples() const { return nbSamples; }

    Sample operator[](int nb) { try { return data[nb]; } catch (...) { throw; } }

    inline std::vector<Sample>::iterator begin() { return data.begin(); }
    inline std::vector<Sample>::iterator end() { return data.end(); }

private:
    Data(std::vector<Sample> data, unsigned int nbSamples, unsigned int nbFeatures) : data(data), nbSamples(nbSamples), nbFeatures(nbFeatures) {}

    std::vector<Sample> data;
    unsigned int nbSamples;
    unsigned int nbFeatures;
};