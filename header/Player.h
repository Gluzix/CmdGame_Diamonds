#pragma once

#include <Coordinates.h>

enum class Way : int {
    Up = 0,
    Down = 1,
    Left = 2,
    Right = 3
};

class Player
{
public:
    Player(const Coordinates &coords);

    void tryToMove(Way way);
    void updatePlayer();
    void restoreCoordinates();
    const Coordinates& pos();

private:
    Coordinates coordinates;
    Coordinates oldCoordinates;
};
