#include "Map.h"
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
                slowerEnemiesPos.push_back(Coordinates(width, height));
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
                fasterEnemiesPos.push_back(Coordinates(width, height));
                drawCaret();
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

bool Map::isObstacleForEnemy(int x, int y, int i)
{
    if(fileReader.getContent()[y][x] == ' ' || fileReader.getContent()[y][x] == '@') {
        slowerEnemiesPos[i] = Coordinates(x, y);
        return true;
    }
    return false;
}

bool Map::isObstacleForPlayer(int x, int y)
{
    if (fileReader.getContent()[y][x] == ' ' || fileReader.getContent()[y][x] == '@'
        || fileReader.getContent()[y][x] == '*' ) {

        return true;
    }
    return false;
}

const Coordinates& Map::getSlowerEnemyCoords(int index)
{
    return slowerEnemiesPos[index];
}

const Coordinates& Map::getFasterEnemyCoords(int index)
{
    return fasterEnemiesPos[index];
}

const Coordinates& Map::getPlayerCoords()
{
    return playerPos;
}

bool Map::hasPlayerTookDiamond(const Coordinates& coords)
{
    if (fileReader.getContent()[coords.y][coords.x] == '*')
    {
        fileReader.modifyContent(coords.y, coords.x, ' ');
        return true;
    }
    else return false;
}

bool Map::hasPlayerSwitchedGate(const Coordinates& coords)
{
    if (fileReader.getContent()[coords.y][coords.x] == 'S')
    {
        return true;
    }
    else return false;
}

bool Map::isGameLost(const Coordinates& coords)
{
    for (const Coordinates& enemyCords : fasterEnemiesPos) {
        if (coords == enemyCords) {
            return true;
        }
    }

    for (const Coordinates& enemyCords : slowerEnemiesPos) {
        if (coords == enemyCords) {
            return true;
        }
    }
    return false;
}

int Map::getPoints()
{
    return points;
}

void Map::removeBarriers()
{
    for (const Coordinates& coords : barrierPos) {
        fileReader.modifyContent(coords.x, coords.y, ' ');
        COORD coord = { static_cast<short>(coords.x), static_cast<short>(coords.y) };
        HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hOutput, coord);
        const char* buff = " ";
        WriteConsoleA(hOutput, buff, 1, NULL, NULL);
    }
}

bool Map::hasPlayerFinished(const Coordinates &coords)
{
    if ((fileReader.getContent()[coords.y][coords.x] == 'O')
        || (fileReader.getContent()[coords.y][coords.x] == 'U')
        || (fileReader.getContent()[coords.y][coords.x] == 'T')) {
        return true;
    }
    return false;
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
