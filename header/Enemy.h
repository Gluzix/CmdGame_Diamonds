#pragma once

#include "Coordinates.h"
#include "Player.h"

class Enemy
{
public:
    Enemy(const Coordinates &beginCoordinates, int moveEveryNTicks, int recognitionDistance);
    virtual ~Enemy() = default;

    bool shouldMove();
    void updatePosition();
    void backToOldPosition();
    void tryToFollowPlayer(const Coordinates& playerCoordinates);
    bool isPlayerNear(const Coordinates& playerCoordinates);
    void updateWay(Way newWay);
    void reverseWay();
    bool hasMoved() const;

    virtual bool canChasePlayer() const;
    virtual void chooseNewWay();

    virtual void updateConsoleCoordinates() = 0;
    virtual Coordinates getCoords();

protected:
    Coordinates coordinates{0, 0};
    Coordinates oldCoordinates{ 0, 0 };
    Way way{Way::Up};
    const int moveEveryNTicks;
    int tickCounter{ 0 };
    int recognitionDistance;
};
