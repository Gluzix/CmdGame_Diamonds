#include "FileReader.h"
#include <fstream>
#include <iostream>

FileReader::FileReader(const std::string& filename)
    : mFilename(filename)
{

}

int FileReader::getFileHeight() const
{
    int height = 0;

    std::fstream fstream(mFilename, std::ios_base::in);
    std::string tempLine;

    if (!fstream) {
        std::cout << "Couldn't open the file";
        return -1;
    }

    while (std::getline(fstream, tempLine)) {
        if (fstream.end) {
            break;
        }
        height++;
    }

    return height;
}

int FileReader::getFileWidth() const
{
    int width = 0;

    std::fstream fstream(mFilename, std::ios_base::in);
    std::string tempLine;

    if (!fstream) {
        std::cout << "Couldn't open the file";
        return -1;
    }

    if (std::getline(fstream, tempLine)) {
        return static_cast<int>(tempLine.size());
    }

    return -1;
}
