#include "Player.h"
#include <iostream>
#include <windows.h>
#include <cstdlib>

Player::Player(const Coordinates& coords)
    : coordinates(coords)
    , oldCoordinates(coords)
{

}

void Player::tryToMove(Way way)
{
    switch(way)
    {
    case Way::Up:
        coordinates.y--;
        break;
    case Way::Down:
        coordinates.y++;
        break;
    case Way::Left:
        coordinates.x--;
        break;
    case Way::Right:
        coordinates.x++;
        break;
    }
}

void Player::restoreCoordinates()
{
    coordinates = oldCoordinates;
}

const Coordinates& Player::pos()
{
    return coordinates;
}

void Player::updatePlayer()
{
    const char *buff=" ";
    const char *enem="@";
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD currentCoords = { coordinates.x, coordinates.y };
    COORD oldCoords = { oldCoordinates.x, oldCoordinates.y };
    SetConsoleCursorPosition(hOutput, oldCoords);
    WriteConsoleA(hOutput, buff, 1, NULL,NULL);
    SetConsoleTextAttribute(hOutput, FOREGROUND_INTENSITY | FOREGROUND_GREEN );
    SetConsoleCursorPosition(hOutput, currentCoords);
    WriteConsoleA(hOutput, enem, 1, NULL,NULL);
    SetConsoleTextAttribute ( hOutput, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    oldCoordinates = coordinates;
}
