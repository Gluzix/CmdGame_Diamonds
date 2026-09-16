#include "Map.h"
#include "Console.h"
#include <iostream>
#include <windows.h>
#include <stdlib.h>

Map::Map()
{

}

void Map::drawMap()
{
    int width = 0;
    int height = 0;

    for (std::string line : fileReader.getContent()) {
        for (const char& ch : line) {
            if (ch == '*') {
                points++;
                drawAsteriks();
            }
            else if (ch == '$') {
                barrierPos.push_back(Coordinates(width, height));
                drawDollar();
            }
            else if (ch == '&') {
                drawAmpersand();
            }
            else if (ch == '#') {
                drawHashtag();
            }
            else if (ch == '@') {
                playerPos = Coordinates(width, height);
                drawCommercialAt();
            }
            else if (ch == '^') {
                drawCaret();
            }
            else if (ch == '%') {
                drawPercent();
            }
            else {
                std::cout << ch;
            }
            width++;
        }
        width = 0;
        height++;
    }
}

bool Map::isInside(const Coordinates& coords) const
{
    const std::vector<std::string>& content = fileReader.getContent();

    return coords.y >= 0
        && coords.y < static_cast<int>(content.size())
        && coords.x >= 0
        && coords.x < static_cast<int>(content[coords.y].size());
}

char Map::charAt(const Coordinates& coords) const
{
    if (!isInside(coords)) {
        return '#';
    }

    return fileReader.getContent()[coords.y][coords.x];
}

bool Map::isObstacleForEnemy(const Coordinates& coords) const
{
    const char ch = charAt(coords);

    return !(ch == ' ' || ch == '*' || ch == '@');
}

bool Map::isObstacleForPlayer(const Coordinates& coords) const
{
    const char ch = charAt(coords);

    return !(ch == ' ' || ch == '*' || ch == '@');
}

const Coordinates& Map::getPlayerCoords()
{
    return playerPos;
}

bool Map::hasPlayerTookDiamond(const Coordinates& coords)
{
    if (charAt(coords) == '*')
    {
        fileReader.modifyContent(coords.y, coords.x, ' ');
        return true;
    }
    else return false;
}

bool Map::hasPlayerSwitchedGate(const Coordinates& coords) const
{
    return charAt(coords) == 'S';
}

int Map::getPoints()
{
    return points;
}

void Map::removeBarriers()
{
    for (const Coordinates& coords : barrierPos) {
        fileReader.modifyContent(coords.y, coords.x, ' ');
        clearCharAt(coords);
    }
}

bool Map::hasPlayerFinished(const Coordinates &coords) const
{
    const char ch = charAt(coords);

    return ch == 'O' || ch == 'U' || ch == 'T';
}

const FileReader& Map::getFileReader()
{
    return fileReader;
}

void Map::drawAsteriks()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    std::cout << '*';
    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Map::drawDollar()
{
    std::cout << '$';
}

void Map::drawAmpersand()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
    std::cout << '&';
    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Map::drawHashtag()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
    std::cout << '#';
    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Map::drawCommercialAt()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    std::cout << '@';
    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Map::drawCaret()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    std::cout << '^';
    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Map::drawPercent()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    std::cout << '%';
    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
