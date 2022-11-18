#include "FileReader.h"
#include <fstream>
#include <iostream>

FileReader::FileReader(const std::string& pathToFile)
{
    std::fstream fstream(pathToFile, std::ios_base::in);
    std::string tempLine;

    if (!fstream) {
        std::cout << "Couldn't open the file";
    }

    while (std::getline(fstream, tempLine)) {
        readFile.push_back(tempLine);
        height++;
    }
    width = tempLine.size();
}

const std::vector<std::string> &FileReader::getContent() const
{
    return readFile;
}

int FileReader::getHeight() const
{
    return height;
}

int FileReader::getWidth() const
{
    return width;
}
