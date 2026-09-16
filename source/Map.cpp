#include "Map.h"
#include "Console.h"
#include <iostream>
#include <windows.h>
#include <stdlib.h>

namespace
{
    constexpr WORD defaultColour = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

    // The single source of truth for every map glyph's colour: drawMap() paints the board
    // with it and Map::redrawTile() repaints one cell with it.
    WORD colourFor(char ch)
    {
        switch (ch) {
        case '*':
            return FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        case '&':
            return FOREGROUND_RED | FOREGROUND_INTENSITY;
        case '^':
            return FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        case '%':
            return FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        case '#':
            return FOREGROUND_INTENSITY;
        case '@':
            return FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        default:
            return defaultColour;
        }
    }

    void printTile(char ch)
    {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, colourFor(ch));
        std::cout << ch;
        SetConsoleTextAttribute(h, defaultColour);
    }
}

void Map::drawMap()
{
    int width = 0;
    int height = 0;

    for (const std::string& line : fileReader.getContent()) {
        for (const char& ch : line) {
            if (ch == '*') {
                points++;
            }
            else if (ch == '$') {
                barrierPos.push_back(Coordinates(width, height));
            }
            else if (ch == '@') {
                playerPos = Coordinates(width, height);
            }

            printTile(ch);
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
        redrawTile(coords);
    }
}

void Map::clearEnemySpawns()
{
    const int height = static_cast<int>(fileReader.getContent().size());

    for (int y = 0; y < height; y++) {
        const int width = static_cast<int>(fileReader.getContent()[y].size());

        for (int x = 0; x < width; x++) {
            const char ch = fileReader.getContent()[y][x];

            if (ch == '&' || ch == '^' || ch == '%') {
                fileReader.modifyContent(y, x, ' ');
            }
        }
    }
}

void Map::redrawTile(const Coordinates& coords) const
{
    if (!isInside(coords)) {
        return;
    }

    const char ch = charAt(coords);

    drawCharAt(coords, ch, colourFor(ch));
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
