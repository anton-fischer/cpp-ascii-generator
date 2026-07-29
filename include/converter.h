#pragma once

#include <iostream>

class Converter
{
public:
    Converter() = default;
    ~Converter() = default;

    void convert(const std::string& filepath);
};
