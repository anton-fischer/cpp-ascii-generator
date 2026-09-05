#include "../include/converter.h"

#include <QImage>

QString Converter::convert(const QString& filepath, const QString& chars /*= "@%#*+=-:. "*/, unsigned int outputWidth /*= 100*/, unsigned int outputHeight /*= 100*/)
{
    if (chars.isEmpty()) return QString();

    QImage image(filepath);

    if (image.isNull()) return QString();

    // scale image
    if (outputWidth < 1) outputWidth = 1;
    if (outputHeight < 1) outputHeight = 1;
    QImage scaled = image.scaled(outputWidth, outputHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    // convert into grayscale
    QImage gray = scaled.convertToFormat(QImage::Format_Grayscale8);

    QString result;
    result.reserve((outputWidth + 1) * outputHeight);

    // actually convert image into ascii
    for (int y = 0; y < gray.height(); ++y)
    {
        const unsigned char *line = gray.constScanLine(y);
        for (int x = 0; x < gray.width(); ++x)
        {
            // 0 equals black, 255 equals white
            const unsigned char brightness = line[x];

            // chose char based on brightness
            const int index = brightness * (chars.length() - 1) / 255;
            result.append(chars[index]);
        }
        result.append('\n');
    }

    return result;
}
