#include "Map.h"
#include "Console.h"
#include <string>
#include <windows.h>

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
        case 'S':
            return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        default:
            return defaultColour;
        }
    }
}

Map::Map(const std::string& pathToFile)
    : fileReader(pathToFile)
{
}

void Map::drawMap()
{
    int x = 0;
    int y = 0;

    for (const std::string& line : fileReader.getContent()) {
        for (const char& ch : line) {
            const Coordinates coords(x, y);

            if (ch == '*') {
                points++;
            }
            else if (ch == '$') {
                barrierPos.push_back(coords);
            }
            else if (ch == '@') {
                playerPos = coords;
            }

            // Every cell is placed by hand. Printing the board as one long stream only
            // lined up while the console happened to be exactly as wide as the map, and
            // wrapped a row early - each row further left than the last - on any other.
            drawCharAt(coords, ch, colourFor(ch));
            x++;
        }
        x = 0;
        y++;
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

const Coordinates& Map::getPlayerCoords() const
{
    return playerPos;
}

bool Map::hasPlayerTakenDiamond(const Coordinates& coords)
{
    if (charAt(coords) == '*')
    {
        fileReader.setCharAt(coords.y, coords.x, ' ');
        return true;
    }
    else return false;
}

bool Map::hasPlayerSwitchedGate(const Coordinates& coords) const
{
    return charAt(coords) == 'S';
}

int Map::getPoints() const
{
    return points;
}

void Map::removeBarriers()
{
    for (const Coordinates& coords : barrierPos) {
        fileReader.setCharAt(coords.y, coords.x, ' ');
        redrawTile(coords);
    }
}

void Map::clearSpawnMarkers()
{
    const std::vector<std::string>& content = fileReader.getContent();
    const int height = static_cast<int>(content.size());

    for (int y = 0; y < height; y++) {
        const std::string& line = content[y];
        const int width = static_cast<int>(line.size());

        for (int x = 0; x < width; x++) {
            const char ch = line[x];

            if (ch == '&' || ch == '^' || ch == '%' || ch == '@') {
                fileReader.setCharAt(y, x, ' ');
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

const FileReader& Map::getFileReader() const
{
    return fileReader;
}
