#include "FastEnemy.h"
#include <windows.h>
#include <string>

FastEnemy::FastEnemy(const Coordinates& beginCoordinates)
    : Enemy(beginCoordinates, 3, 6)
{

}

void FastEnemy::updateConsoleCoordinates()
{
    std::string buffer = " ";
    std::string enemy = "^";
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD currentCoords = { coordinates.x, coordinates.y };
    COORD oldCoords = { oldCoordinates.x, oldCoordinates.y };
    SetConsoleCursorPosition(hOutput, oldCoords);
    WriteConsoleA(hOutput, buffer.c_str(), 1, NULL, NULL);
    SetConsoleTextAttribute(hOutput, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    SetConsoleCursorPosition(hOutput, currentCoords);
    WriteConsoleA(hOutput, enemy.c_str(), 1, NULL, NULL);
    SetConsoleTextAttribute (hOutput, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    oldCoordinates = coordinates;
}
