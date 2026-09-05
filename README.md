# Ascii Art Generator

A simple desktop application built with Qt/C++ that converts images into ASCII art.

## Features

- Load an image (`jpg`, `jpeg`, `png`, `bmp`, `tiff`, `gif`) and convert it to ASCII art
- Click the generated ASCII art to copy it to the clipboard
- Customizable settings such as size and which characters to use

## Requirements

- CMake 3.16+
- Qt 6 (or Qt 5) with the Widgets component
- A C++17 compiler (tested with MinGW on Windows)

## Building

```powershell
cmake -S . -B build -DCMAKE_PREFIX_PATH="<path-to-your-Qt-installation>"
cmake --build build
```

The resulting `ascii-generator` executable will be placed in the build directory.


## License

This project is licensed under the [MIT License](LICENSE).
