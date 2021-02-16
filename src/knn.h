#pragma once

#include <string>

#include "data.h"
#include "featurevector.h"

class Knn
{
public:
    Knn(Data trainingData, int k) : data(trainingData), k(k) { }
    Knn(Data trainingData) : data(trainingData), k(findBestK()) { }

    std::string predict(const FeatureVector& inputVector);

protected:
    int findBestK();
    virtual float similarity(const FeatureVector& vec1, const FeatureVector& vec2);

private:
    Data data;
    int k;
};

class KnnLinear : public Knn
{
public:
    KnnLinear(Data trainingData, int k) : Knn(trainingData, k) { }
    KnnLinear(Data trainingData) : Knn(trainingData) { }

protected:
    virtual float similarity(const FeatureVector& vec1, const FeatureVector& vec2) override;
};

class KnnCosine : public Knn
{
public:
    KnnCosine(Data trainingData, int k) : Knn(trainingData, k) { }
    KnnCosine(Data trainingData) : Knn(trainingData) { }

protected:
    virtual float similarity(const FeatureVector& vec1, const FeatureVector& vec2) override;
};

class KnnCosinePondered : public Knn
{
public:
    KnnCosinePondered(Data trainingData, int k) : Knn(trainingData, k) { }
    KnnCosinePondered(Data trainingData) : Knn(trainingData) { }

protected:
    virtual float similarity(const FeatureVector& vec1, const FeatureVector& vec2) override;
};

class KnnManhattan : public Knn
{
public:
    KnnManhattan(Data trainingData, int k) : Knn(trainingData, k) { }
    KnnManhattan(Data trainingData) : Knn(trainingData) { }

protected:
    virtual float similarity(const FeatureVector& vec1, const FeatureVector& vec2) override;
};