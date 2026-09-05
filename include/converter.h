#pragma once

#include <QString>

class Converter
{
public:
    Converter() = default;
    ~Converter() = default;

    QString convert(const QString& filepath, const QString& chars = "@%#*+=-:. ", unsigned int outputWidth = 100, unsigned int outputHeight = 100);
};
