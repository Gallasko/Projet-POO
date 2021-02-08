#include <iostream>

#include "data.h"

int main(int argc, char *argv[])
{

    Data data;

    data.load("Digits/digits.svm");

    std::cout << data.getNbSamples() << std::endl;

    auto d = data.getData()[0];

    std::cout << d.getTag() << std::endl;

    auto d1 = data.getData()[1];

    std::cout << d1.getTag() << std::endl;

    auto d2 = data.getData()[2];

    std::cout << d2.getTag() << std::endl;

	return 0;
}