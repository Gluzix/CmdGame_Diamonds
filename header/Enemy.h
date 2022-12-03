#pragma once

#include "Coordinates.h"
#include "Player.h"

class Enemy
{
public:
    Enemy(int speed);
    void updatePosition();
    void backToOldPosition();
    bool isPlayerNear(const Coordinates& coordinates);

    virtual void updateConsoleCoordinates() = 0;
    virtual Coordinates getCoords();

protected:
    Coordinates coordinates{0, 0};
    Coordinates oldCoordinates{ 0, 0 };
    Way way{Way::Up};
    int speed;
};
