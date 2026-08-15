#include "../include/settings.h"

Settings& Settings::instance()
{
    // instance is only created once
    static Settings instance;
    return instance;
}

void Settings::setChars(const QString& chars)
{
    this->chars = chars;
}

void Settings::setWidth(unsigned int width)
{
    this->width = width;
}

void Settings::setHeight(unsigned int height)
{
    this->height = height;
}

void Settings::setInvert(bool invert)
{
    this->invert = invert;
}

QString Settings::getChars()
{
    return this->chars;
}

unsigned int Settings::getWidth()
{
    return this->width;
}

unsigned int Settings::getHeight()
{
    return this->height;
}

bool Settings::getInvert()
{
    return this->invert;
}
