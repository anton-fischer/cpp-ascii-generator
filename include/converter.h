#pragma once

#include <QString>

class Converter
{
public:
    Converter() = default;
    ~Converter() = default;

    QString convert(const QString& filepath, const unsigned int outputWidth = 100, const QString& chars = "@%#*+=-:. ");
};
