#include "SlowEnemy.h"
#include <windows.h>

SlowEnemy::SlowEnemy(const Coordinates& beginCoordinates) :
    Enemy(beginCoordinates, 4, 4)
{

}

void SlowEnemy::updateConsoleCoordinates()
{
    const char *buff=" ";
    const char *enem="&";
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD currrentCoords = { coordinates.x, coordinates.y };
    COORD oldCoords = { coordinates.x, coordinates.y };
    SetConsoleCursorPosition(hOutput, oldCoords);
    WriteConsoleA(hOutput, buff, 1, NULL, NULL);
    SetConsoleTextAttribute(hOutput, FOREGROUND_RED | FOREGROUND_INTENSITY);
    SetConsoleCursorPosition(hOutput, currrentCoords);
    WriteConsoleA(hOutput, enem, 1, NULL, NULL);
    SetConsoleTextAttribute (hOutput, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    oldCoordinates = coordinates;
}
