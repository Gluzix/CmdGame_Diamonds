#pragma once

#include "Coordinates.h"
#include "Player.h"

class Enemy
{
public:
    Enemy(const Coordinates &beginCoordinates, int speed, int recognitionDistance);
    void updatePosition();
    void backToOldPosition();
    void tryToFollowPlayer(const Coordinates& playerCoordinates);
    bool isPlayerNear(const Coordinates& playerCoordinates);
    void updateWay(Way way);


    virtual void updateConsoleCoordinates() = 0;
    virtual Coordinates getCoords();

protected:
    Coordinates coordinates{0, 0};
    Coordinates oldCoordinates{ 0, 0 };
    Way way{Way::Up};
    int speed;
    int recognitionDistance;
};
