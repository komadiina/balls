#include <iostream>

#include "./Scene.hpp"

int main(int argC, char **argV)
{
    int width = std::stoi(argV[1]),
        height = std::stoi(argV[2]),
        numObjects = std::stoi(argV[3]);

    Scene scenery = Scene(width, height, numObjects);
    scenery.drawScene();
    scenery.showInfo(std::cout, false);

    return EXIT_SUCCESS;
}