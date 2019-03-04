#include "punctation.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
void punctation::update_points()
{
    points++;
}
void punctation::show_points()
{
    char buf[16];
    sprintf(buf, "Diamonds: %d/12", points);
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {48,26};
    SetConsoleCursorPosition(hOutput, coord);
    WriteConsoleA(hOutput, buf, 16, NULL, NULL);
}
int punctation::return_of_players_points()
{
    return points;
}
