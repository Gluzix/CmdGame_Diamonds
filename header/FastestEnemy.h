#pragma once

#include "Enemy.h"

class FastestEnemy : public Enemy
{
public:
    FastestEnemy(const Coordinates &beginCoordinates);

    bool canChasePlayer() const override;
    void chooseNewWay() override;

    void updateConsoleCoordinates() override;
};
