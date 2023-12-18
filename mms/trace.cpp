#include <iostream>
#include <fstream>
#include <limits>
#include "./include/Scene.hpp"
#include "./include/Utilities.hpp"

int main(int argC, char **argV)
{
    char *traceImgPath = argV[1];
    Bitmap file;
    file.open(traceImgPath);

    std::cout << std::format("Opened: {}\n", argV[1]);

    const PixelMatrix pm = file.toPixelMatrix();
    const uint16_t height = pm.size(), width = pm.at(0).size();

    std::cout << std::format("Initialized the pixel matrix.\n");

    std::vector<CircleObj> traced = Utilities::trace(pm, 20.0f);

    std::cout << std::format("Traced the circles from source image.\n");

    CircleObj *data = traced.data();
    Scene scenery(width, height, 0xFF'FF - 1);
    scenery.setObjects(data);
    scenery.maxObj = traced.size();
    scenery.drawScene();

    std::cout << std::format("Drew a scene ({}, {}) with max {} objects.\n", width, height, scenery.maxObj);

    return EXIT_SUCCESS;
}