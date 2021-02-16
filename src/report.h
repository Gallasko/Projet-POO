#pragma once

#include <iostream>
#include <string>

class ClassificationReport
{
public:
    ClassificationReport(unsigned int nbTags);
    ~ClassificationReport();

    void addResult(int predicted, int expected);
    
    std::string toString();

    friend std::ostream& operator<<(std::ostream& os, const ClassificationReport& rhs);

private:
    unsigned int nbTags;
    unsigned int **confusionMatrix;
    unsigned int nbOk;
    unsigned int nbNOk;
};