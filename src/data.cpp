#include "data.h"

void Data::load(std::string path)
{
    std::fstream fs;
    fs.open(path, std::fstream::in);

    if(fs.is_open())
    {
        std::string buffer;
        std::string tag;
        std::vector<std::string> fVector;

        std::getline(fs, buffer);
        nbSamples = std::atoi(buffer.c_str());

        std::getline(fs, buffer);
        nbFeatures = std::atoi(buffer.c_str());

        for(int i = 0; i < nbSamples; i++)
        {
            std::getline(fs, tag, ' ');
            
            for(int j = 0; j < nbFeatures - 1; j++)
            {
                std::getline(fs, buffer, ' ');
                fVector.push_back(buffer);
            }

            std::getline(fs, buffer);
            fVector.push_back(buffer);

            Sample sample(tag, fVector);
            data.push_back(sample);

            std::vector<std::string>().swap(fVector);
        }
    }
    else
    {
        std::cout << "Error opening file" << std::endl;
    }
}

Data Data::split(int pos)
{
    if(pos < data.size())
    {
        std::vector<Sample> splitLow(data.begin(), data.begin() + pos);
        std::vector<Sample> splitHigh(data.begin() + pos, data.end() );

        Data halfData(splitHigh, data.size() - pos, nbFeatures);

        data = splitLow;
        nbSamples = pos;

        return halfData;
    }
    else
        return Data();
}


Data Data::split(float percentage)
{
    return split(static_cast<int>(data.size() * percentage));
}

void Data::append(Data data)
{
    this->data.insert(this->data.end(), data.begin(), data.end());
    nbSamples = this->data.size();
}
