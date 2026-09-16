#include "FileReader.h"
#include <fstream>
#include <iostream>

FileReader::FileReader(const std::string& pathToFile)
{
    std::fstream fstream(pathToFile, std::ios_base::in);

    if (!fstream) {
        std::cerr << "Couldn't open the file: " << pathToFile << std::endl;
        return;
    }

    std::string tempLine;

    while (std::getline(fstream, tempLine)) {
        readFile.push_back(tempLine);
        height++;

        const int lineWidth = static_cast<int>(tempLine.size());

        if (lineWidth > width) {
            width = lineWidth;
        }
    }
}

const std::vector<std::string> &FileReader::getContent() const
{
    return readFile;
}

void FileReader::modifyContent(int y, int x, char ch)
{
    readFile[y][x] = ch;
}

int FileReader::getHeight() const
{
    return height;
}

int FileReader::getWidth() const
{
    return width;
}
