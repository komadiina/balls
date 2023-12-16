#pragma once

#include <functional>
#include "./Bitmap/bitmap.h"

const Pixel BLACK = Pixel(0, 0, 0), WHITE = Pixel(255, 255, 255);
const Pixel RED = Pixel(255, 0, 0), GREEN = Pixel(0, 255, 0), BLUE = Pixel(0, 0, 255);

class BlendMode
{
private:
    std::function<Pixel(Pixel, Pixel)> lambda;

public:
    BlendMode(const std::function<Pixel(Pixel, Pixel)> &mode)
    {
        lambda = mode;
    }

    Pixel operator()(const Pixel &a, const Pixel &b)
    {
        return this->lambda(a, b);
    }
};

namespace BlendModes
{
    BlendMode Additive = BlendMode(
        [](const Pixel &a, const Pixel &b)
        {
            return a + b;
        });
    BlendMode Screen = BlendMode(
        [](const Pixel &a, const Pixel &b)
        {
            return (WHITE - (WHITE - a)) * (WHITE - b);
        });
    BlendMode ScreenInvert = BlendMode(
        [](const Pixel &a, const Pixel &b)
        {
            return (BLACK + (BLACK + a)) * (BLACK + b);
        });
}