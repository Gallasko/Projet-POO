#include <iostream>

#include "data.h"
#include "knn.h"
#include "report.h"

#define NBTAGS 10

int main(int argc, char *argv[])
{
    Data data;

    data.load("Digits/digits.svm");

    std::cout << data.getNbSamples() << std::endl;

    Data testData = data.split(0.6f);

    std::cout << data.getNbSamples() << std::endl;
    std::cout << testData.getNbSamples() << std::endl;

    Knn knn(data, 1);
    KnnLinear knnLinear(data, 3);
    KnnCosine knnCosine(data, 3);
    KnnCosinePondered knnCosinePondered(data, 3);
    KnnManhattan knnManhattan(data, 3);

    ClassificationReport linearReport(NBTAGS);
    ClassificationReport cosineReport(NBTAGS);
    ClassificationReport cosinePonderedReport(NBTAGS);
    ClassificationReport manhattanReport(NBTAGS);

    for(int i = 0; i < testData.getNbSamples(); i++)
    {
        auto d = testData.getData()[i];

        linearReport.addResult(std::stoi(knnLinear.predict(d.getFeature())), std::stoi(d.getTag()));
        cosineReport.addResult(std::stoi(knnCosine.predict(d.getFeature())), std::stoi(d.getTag()));
        cosinePonderedReport.addResult(std::stoi(knnCosinePondered.predict(d.getFeature())), std::stoi(d.getTag()));
        manhattanReport.addResult(std::stoi(knnManhattan.predict(d.getFeature())), std::stoi(d.getTag()));

        //std::cout << "Predict tag " << d.getTag() << " as: " << std::endl;
        //std::cout << knn.predict(d.getFeature()) << std::endl;
        //std::cout << knnLinear.predict(d.getFeature()) << std::endl;
        //std::cout << knnCosine.predict(d.getFeature()) << std::endl;
        //std::cout << knnManhattan.predict(d.getFeature()) << std::endl;
    }

    std::cout << "Linear Report" << std::endl;
    std::cout << linearReport;

    std::cout << "Cosine Report" << std::endl;
    std::cout << cosineReport;

    std::cout << "Cosine Pondered Report" << std::endl;
    std::cout << cosinePonderedReport;

    std::cout << "Manhattan Report" << std::endl;
    std::cout << manhattanReport;

	return 0;
}