#pragma once

#include <cstdint>
#include <iostream>
#include <format>
#include "./Vector2.hpp"
#include "../../Bitmap/bitmap.h"

uint16_t ID = 1;

class CircleObj
{
public:
    Vector2<uint16_t> pos;
    float mass = 0.0f;
    float diameter;

    uint16_t id;
    Pixel initialColor, endColor;

public:
    CircleObj() {}

    CircleObj(const Vector2<uint16_t> &pos, float mass, float diameter) : pos(pos), mass(mass), diameter(diameter)
    {
        this->id = ID++;
    }

    void setGradient(const Pixel &initial, const Pixel &end)
    {
        initialColor = initial;
        endColor = end;
    }

    void print(std::ostream &os = std::cout)
    {
        os << std::format("[{}]  (X, Y): ({}, {}), Mass: {:.2f}, Diameter: {:.2f}", this->id, pos.x, pos.y, mass, diameter) << std::endl
           << std::format("\tRGB({}, {}, {}) -> RGB({}, {}, {})", initialColor.red, initialColor.green, initialColor.blue, endColor.red, endColor.green, endColor.blue) << std::endl;
        ;
    }
};