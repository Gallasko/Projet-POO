#include "report.h"

ClassificationReport::ClassificationReport(unsigned int nbTags) : nbTags(nbTags), nbOk(0), nbNOk(0)
{
    confusionMatrix = new unsigned int*[nbTags];

    for(int i = 0; i < nbTags; i++)
    {
        confusionMatrix[i] = new unsigned int[nbTags];

        for(int j = 0; j < nbTags; j++)
        {
            confusionMatrix[i][j] = 0;
        }
    }
}

ClassificationReport::~ClassificationReport()
{
    for(int i = 0; i < nbTags; i++)
    {
        delete[] confusionMatrix[i];
    }

    delete[] confusionMatrix;
}

void ClassificationReport::addResult(int predicted, int expected)
{
    if(predicted == expected)
        nbOk++;
    else
        nbNOk++;

    confusionMatrix[predicted][expected]++;
}

std::string ClassificationReport::toString()
{
    return " ";
}

std::ostream& operator<<(std::ostream& os, const ClassificationReport& rhs)
{
    os << "### Classification Result ###" << std::endl;
    os << "Precision: " << static_cast<float>(rhs.nbOk) / (rhs.nbOk + rhs.nbNOk) << ", Error Rate: " << static_cast<float>(rhs.nbNOk) / (rhs.nbOk + rhs.nbNOk) << std::endl;
    os << "Correct Tag found: " << rhs.nbOk << ", Number of error: " << rhs.nbNOk << std::endl;
    os << "### Confusion Matrix ###" << std::endl;

    for(int i = 0; i < rhs.nbTags; i++)
    {
        for(int j = 0; j < rhs.nbTags; j++)
        {
            os << rhs.confusionMatrix[i][j] << " ";
        }
        os << std::endl; 
    }

    os << "### End Report ###" << std::endl;

    return os; 
}

