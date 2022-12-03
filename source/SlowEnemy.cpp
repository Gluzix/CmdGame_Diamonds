#include "SlowEnemy.h"
#include <windows.h>

SlowEnemy::SlowEnemy(int speed) :
    speed(speed)
{

}

void SlowEnemy::updateConsoleCoordinates()
{
    const char *buff=" ";
    const char *enem="&";
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD currrentCoords = { coordinates.x, coordinates .y };
    COORD oldCoords = { coordinates.x, coordinates .y };
    SetConsoleCursorPosition(hOutput, oldCoords);
    WriteConsoleA(hOutput, buff, 1, NULL, NULL);
    SetConsoleTextAttribute(hOutput, FOREGROUND_RED | FOREGROUND_INTENSITY);
    SetConsoleCursorPosition(hOutput, currrentCoords);
    WriteConsoleA(hOutput, enem, 1, NULL, NULL);
    SetConsoleTextAttribute (hOutput, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    oldCoordinates = coordinates;
}

bool SlowEnemy::isPlayerNear(const Coordinates &playerCoords)
{
    bool decision = false;
    int disparity_x = coordinates.x - playerCoords.x;
    int disparity_y = coordinates.y - playerCoords.y;
    if (disparity_x < 0)disparity_x = disparity_x * (-1);
    if (disparity_y < 0)disparity_y = disparity_y * (-1);
    if ((disparity_x <= 8) && (disparity_y <= 5))
    {
        decision = true;
        if (round == 4)
        {
            if (x_or_y == 0)
            {
                round = 0;
                if (pos_x > x)
                {
                    pos_x--;
                }
                else if (pos_x < x)
                {
                    pos_x++;
                }
                else if (pos_x == x)
                {
                    if (pos_y > y)
                    {
                        pos_y--;
                    }
                    else if (pos_y < y)
                    {
                        pos_y++;
                    }
                }
                x_or_y = 1;
            }
            else if (x_or_y == 1)
            {
                round = 0;
                if (pos_y > y)
                {
                    pos_y--;
                }
                else if (pos_y < y)
                {
                    pos_y++;
                }
                else if (pos_y == y)
                {
                    if (pos_x > x)
                    {
                        pos_x--;
                    }
                    else if (pos_x < x)
                    {
                        pos_x++;
                    }
                }
                x_or_y = 0;
            }
        }
        else round++;
        who_used_round = 1;
    }
    return decision;

}
