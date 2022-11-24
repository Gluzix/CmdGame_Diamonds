#include "Punctation.h"
#include <sstream>
#include <windows.h>

Punctation::Punctation(int maxPunctation)
    : maxPunctation(maxPunctation)
{

}

void Punctation::update()
{
    punctation++;
}

void Punctation::show()
{
    std::stringstream ss;
    ss << "Diamonds: " << punctation << "/" << maxPunctation;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { 48,26 };
    SetConsoleCursorPosition(hOutput, coord);
    std::string punctationStr = ss.str();
    WriteConsoleA(hOutput, punctationStr.c_str(), punctationStr.length(), NULL, NULL);
}

int Punctation::get()
{
    return punctation;
}
