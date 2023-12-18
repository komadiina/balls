#pragma once

#include <cmath>

#include "./BlendModes.hpp"
#include "./CircleObj.hpp"
#include "./Utilities.hpp"
#include "../../Bitmap/bitmap.h"

class Scene
{
public:
    CircleObj *objects;
    PixelMatrix pm;
    uint16_t maxObj;
    uint16_t width, height;

public:
    Scene(uint16_t width, uint16_t height, uint16_t maxObjects = 255, bool demo = false)
        : width(width), height(height), maxObj(maxObjects)
    {
        // Blank (black) scene
        for (int i = 0; i < height; i++)
        {
            pm.push_back(std::vector<Pixel>());
            for (int j = 0; j < width; j++)
                pm[i].push_back(Pixel(0, 0, 0));
        }

        objects = new CircleObj[maxObjects];

        if (demo)
            for (int i = 0; i < maxObjects; i++)
            {
                objects[i] = CircleObj(Utilities::createRandomCircle(width, height));
                objects[i].setGradient(Utilities::createRandomColor(), Utilities::createRandomColor());
            }
    }

    void setObjects(CircleObj *objects)
    {
        delete[] this->objects;
        this->objects = objects;
    }

    void drawScene(std::string outputFile = "output.bmp")
    {
        for (int i = 0; i < maxObj; i++)
            drawObject(objects[i]);

        Bitmap bmp;
        bmp.fromPixelMatrix(this->pm);
        bmp.save(outputFile);
    }

    void showInfo(std::ostream &os = std::cout, bool showPixels = false)
    {
        os << std::format("{}x{}, Max. objects: {}\n", width, height, maxObj);

        for (int i = 0; i < maxObj; i++)
            objects[i].print(os);

        if (showPixels)
        {
            for (const auto &row : pm)
                for (const auto &elem : row)
                    os << elem << std::endl;
        }
    }

private:
    void drawObject(const CircleObj &obj)
    {
        uint16_t x = obj.pos.x - obj.diameter / 2, y = obj.pos.y - obj.diameter / 2;
        Vector2 it = {x, y};

        Utilities::nonnegative(&x), Utilities::nonnegative(&y);

        for (uint16_t y = obj.pos.y - obj.diameter / 2; y < obj.pos.y + obj.diameter && y < height; y++)
            for (uint16_t x = obj.pos.x - obj.diameter / 2; x < obj.pos.x + obj.diameter && x < width; x++)
            {
                if (!isInArea({x, y}, obj))
                    continue;
                else
                    colorIn({x, y}, obj);
            }
    }

    bool isInArea(const Vector2<uint16_t> &coords, const CircleObj &circle)
    {
        return pow(circle.pos.x - coords.x, 2) + pow(circle.pos.y - coords.y, 2) <= pow(circle.diameter / 2, 2);
    }

    void colorIn(const Vector2<uint16_t> &coords, const CircleObj &circle)
    {
        float_t x = euclideanDistance(coords, circle.pos);
        float_t max = circle.diameter / 2;
        float_t distScale = ((max - x) / max);

        pm[coords.y][coords.x] =
            BlendModes::Additive(circle.initialColor * distScale, pm[coords.y][coords.x]);
    }

    float_t euclideanDistance(const Vector2<uint16_t> &a, const Vector2<uint16_t> &b)
    {
        return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    }
};