#include "Score.h"
#include <sstream>
#include <windows.h>

Score::Score(int total, int row)
    : total(total)
    , row(row)
{

}

void Score::update()
{
    collected++;
}

void Score::show() const
{
    std::stringstream ss;
    ss << "Diamonds: " << collected << "/" << total;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { 48, static_cast<SHORT>(row) };
    SetConsoleCursorPosition(hOutput, coord);
    std::string scoreLine = ss.str();
    WriteConsoleA(hOutput, scoreLine.c_str(), static_cast<DWORD>(scoreLine.length()), nullptr, nullptr);
}

int Score::get() const
{
    return collected;
}
