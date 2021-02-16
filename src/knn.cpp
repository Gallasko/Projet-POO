#include "knn.h"

#include <cmath>

//Helper stuct

struct SimilarityResult
{
    std::string tag = "0";
    float similarity = 0.0f;

    inline SimilarityResult& operator=(const SimilarityResult& rhs)
    {
        tag = rhs.tag;
        similarity = rhs.similarity;

        return *this;
    }
};

struct SimilarityFrequency
{
    SimilarityFrequency(std::string tag, unsigned int count) : tag(tag), count(count) {}

    std::string tag = "0";
    unsigned int count = 0;
};

//Helper func

template<typename Container> 
int findTag(Container container, std::string tag)
{
    for(auto it = container.begin(); it < container.end(); it++)
        if((*it).tag == tag)
            return it - container.begin();

    return -1;
}

std::string Knn::predict(const FeatureVector& inputVector)
{
    SimilarityResult nearestNeighbour[k];

    int i = 0;
    float sim = 0.0f;
    SimilarityResult buffer;
    SimilarityResult buffer2;    
    
    for(auto trainingSample : data) 
    {
        sim = similarity(inputVector, trainingSample.getFeature());

        for(i = 0; i < k; i++)
        {
            if(nearestNeighbour[i].similarity < sim)
            {
                buffer = nearestNeighbour[i];
                nearestNeighbour[i].tag = trainingSample.getTag();
                nearestNeighbour[i].similarity = sim;

                i++;
                break;
            }
        }

        for(; i < k; i++)
        {
            buffer2 = nearestNeighbour[i];
            nearestNeighbour[i] = buffer;
            buffer = buffer2;
        }
    }

    int maxCount = 0;
    int indexMaxCount = -1; 
    std::vector<SimilarityFrequency> neighbourFrequencies;

    for(int i = 0; i < k; i++)
    {
        auto it = findTag(neighbourFrequencies, nearestNeighbour[i].tag);

        if(it == -1)
        {
            SimilarityFrequency frequency(nearestNeighbour[i].tag, 1);
            neighbourFrequencies.push_back(frequency);

            if(indexMaxCount == -1)
            {
                indexMaxCount = 0;
                maxCount = 1;
            }
        }
        else
        {
            neighbourFrequencies.at(it).count++;
            
            if(neighbourFrequencies.at(it).count > maxCount)
            {
                maxCount = neighbourFrequencies.at(it).count;
                indexMaxCount = it;
            }
            
        }
    }

    return neighbourFrequencies.at(indexMaxCount).tag;
}

int Knn::findBestK()
{

    return 0;
}


float Knn::similarity(const FeatureVector& vec1, const FeatureVector& vec2)
{
    if(vec1 == vec2)
        return 1.0f;
    else
        return 0.0f;
}

float KnnLinear::similarity(const FeatureVector& vec1, const FeatureVector& vec2)
{
    int size = vec1.size() < vec2.size() ? vec1.size() : vec2.size();

    float result = 0.0f;

    for(int i = 0; i < size; i++)
        result += (std::stof(vec1[i]) - std::stof(vec2[i])) * (std::stof(vec1[i]) - std::stof(vec2[i]));

    if(result == 0.0f)
        return static_cast<unsigned int>(-1);
    else
        return 1 / std::sqrt(result);
}

float KnnCosine::similarity(const FeatureVector& vec1, const FeatureVector& vec2)
{
    int size = vec1.size() < vec2.size() ? vec1.size() : vec2.size();

    float result = 0.0f;

    for(int i = 0; i < size; i++)
        result += (std::stof(vec1[i]) * std::stof(vec2[i]));

    return result / (vec1.getNorme() * vec2.getNorme());
}

float KnnCosinePondered::similarity(const FeatureVector& vec1, const FeatureVector& vec2)
{
    int size = vec1.size() < vec2.size() ? vec1.size() : vec2.size();

    float result = 0.0f;
    float result2 = 0.0f;

    for(int i = 0; i < size; i++)
        result += (std::stof(vec1[i]) * std::stof(vec2[i]));

    for(int i = 0; i < size; i++)
        result2 += (std::stof(vec1[i]) - std::stof(vec2[i])) * (std::stof(vec1[i]) - std::stof(vec2[i]));

    if(result2 == 0.0f)
        return static_cast<unsigned int>(-1);
    else
        return (1 / std::sqrt(result2)) * (result / (vec1.getNorme() * vec2.getNorme()));
}

float KnnManhattan::similarity(const FeatureVector& vec1, const FeatureVector& vec2)
{
    int size = vec1.size() < vec2.size() ? vec1.size() : vec2.size();

    float result = 0.0f;

    for(int i = 0; i < size; i++)
        result += std::abs(std::stof(vec1[i]) - std::stof(vec2[i]));

    if(result == 0.0f)
        return static_cast<unsigned int>(-1);
    else
        return 1 / result;
}

