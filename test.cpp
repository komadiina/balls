#include <iostream>

int main()
{
    int lower, upper, value;
    std::cin >> lower;
    std::cin >> upper;
    std::cin >> value;

    float normalized = (float)(value - lower) / (float)(upper - lower);
    std::cout << normalized << std::endl;

    float multiplied = normalized * 0.33f;
    std::cout << multiplied << std::endl;

    int expanded = multiplied * 255;
    std::cout << expanded << std::endl;
}