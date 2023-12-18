#pragma once

#include "./CircleObj.hpp"
#include "../../Bitmap/bitmap.h"
#include <random>
#include <algorithm>

class Utilities
{
public:
    static CircleObj createRandomCircle(uint16_t width, uint16_t height)
    {
        std::default_random_engine generator = initEngine(generateSeed());

        uint16_t x = generator() % width,
                 y = generator() % height;

        std::float_t mass = (std::float_t)((int)((std::float_t)generator() / 11.0f) % 15);
        std::float_t diameter = 1.0f + (std::float_t)((int)((std::float_t)generator()) % (width / 4));

        Vector2 pos = {x, y};
        return CircleObj(pos, mass, diameter);
    }

    static Pixel createRandomColor()
    {
        std::default_random_engine generator = initEngine(generateSeed());
        return Pixel(generator() % 255, generator() % 255, generator() % 255);
    }

    static std::default_random_engine initEngine(std::string seed)
    {
        std::random_shuffle(seed.begin(), seed.end());
        std::seed_seq seedSeq(seed.begin(), seed.end());
        std::default_random_engine generator(seedSeq);

        return generator;
    }

    static void nonnegative(uint16_t *a)
    {
        if (*a < 0)
            *a = 0;
    }

    template <typename _Type>
    static _Type clamp(_Type val, _Type min, _Type max)
    {
        return std::max(min, std::min(max, val));
    }

    template <typename _Type = int>
    static _Type normalize(_Type val, _Type min, _Type max)
    {
        return (val - min) / (max - min);
    }

    static std::vector<CircleObj> trace(const PixelMatrix &matrix, float defaultDiameter = 20)
    {
        std::vector<CircleObj> tracedCircles;
        uint16_t x = 0, y = 0;

        for (y = 0; y < matrix.size(); ++y)
            for (x = 0; x < matrix[y].size(); ++x)
                if (matrix.at(y).at(x) == WHITE)
                {
                    Vector2<uint16_t> pos = {x, y};
                    CircleObj circle = CircleObj(
                        pos, 0.0f, defaultDiameter / 2.0f + rand() % 20);
                    circle.setGradient(createRandomColor(), createRandomColor());

                    tracedCircles.push_back(circle);
                }

        return tracedCircles;
    }

private:
    static std::string generateSeed()
    {
        std::string seed = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuwxyz" + std::to_string(time(NULL) + (rand() % 69));
        std::random_shuffle(seed.begin(), seed.end());

        return seed;
    }
};