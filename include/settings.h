#pragma once

#include <QString>

class Settings
{
public:
    // singleton
    static Settings& instance();

    void setChars(const QString& chars);
    void setWidth(unsigned int width);
    void setHeight(unsigned int height);

    QString getChars();
    unsigned int getWidth();
    unsigned int getHeight();

private:
    Settings() = default;
    ~Settings() = default;

    // copying not allowed
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

    QString chars = "@%#*+=-:. ";
    unsigned int width = 50;
    unsigned int height = 50;

};
