#include "Punctation.h"
#include <sstream>
#include <windows.h>

Punctation::Punctation(int maxPunctation, int row)
    : maxPunctation(maxPunctation)
    , row(row)
{

}

void Punctation::update()
{
    punctation++;
}

void Punctation::show() const
{
    std::stringstream ss;
    ss << "Diamonds: " << punctation << "/" << maxPunctation;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { 48, static_cast<SHORT>(row) };
    SetConsoleCursorPosition(hOutput, coord);
    std::string punctationStr = ss.str();
    WriteConsoleA(hOutput, punctationStr.c_str(), static_cast<DWORD>(punctationStr.length()), nullptr, nullptr);
}

int Punctation::get() const
{
    return punctation;
}
