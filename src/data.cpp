#include "data.h"

Data::Data()
{

}

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
        }
    }
    else
    {
        std::cout << "Error opening file" << std::endl;
    }
}