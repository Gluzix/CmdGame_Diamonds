#include "FileReader.h"
#include <fstream>
#include <iostream>

FileReader::FileReader(const std::string& filename)
    : mFilename(filename)
{

}

int FileReader::getFileHeight()
{
    int height = 0;

    std::fstream fstream(mFilename, std::ios_base::in);
    std::string tempLine;

    if (!fstream) {
        std::cout << "Couldn't open the file";
        return 0;
    }

    while (std::getline(fstream, tempLine)) {
        if (fstream.end) {
            break;
        }
        height++;
    }

    return height;
}

int FileReader::getFileWidth()
{

    int i, w, width, height;
    char buforek;
    width = 1;
    height = 1;
    FILE* plik;
    plik = fopen(str, "r");
    if (plik == NULL)
    {
        cout << "Error";
    }
    else
    {
        while (fscanf_s(plik, "%c", &buforek) != EOF)
        {
            width++;
            if (buforek == '\n')
            {
                height++;
            }
        }
    }
    fclose(plik);
    return width;
}
