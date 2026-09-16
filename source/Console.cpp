#include "Console.h"

namespace
{
    constexpr WORD defaultColour = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

    void writeCharAt(const Coordinates& coordinates, char character, WORD colour)
    {
        HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD consoleCoords = { static_cast<SHORT>(coordinates.x), static_cast<SHORT>(coordinates.y) };

        SetConsoleTextAttribute(hOutput, colour);
        SetConsoleCursorPosition(hOutput, consoleCoords);
        WriteConsoleA(hOutput, &character, 1, NULL, NULL);
        SetConsoleTextAttribute(hOutput, defaultColour);
    }
}

void drawCharAt(const Coordinates& coordinates, char character, WORD colour)
{
    writeCharAt(coordinates, character, colour);
}

void clearCharAt(const Coordinates& coordinates)
{
    writeCharAt(coordinates, ' ', defaultColour);
}
