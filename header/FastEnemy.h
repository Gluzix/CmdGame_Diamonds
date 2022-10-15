#ifndef FAST_ENEMY
#define FAST_ENEMY

#include "Enemy.h"

class FastEnemy : public Enemy
{
public:
    FastEnemy(int x, int y);
    ~FastEnemy();
    virtual void UpdatePosition();
    virtual void UpdateConsoleCoordinates();
    virtual void BackToOldPosition();
    virtual bool IsPlayerNear(int, int);
    virtual int GetX();
    virtual int GetY();

private:
    int m_posX;
    int m_posY;
    int m_oldPosX;
    int m_oldPosY;
    int m_way;
    int m_round;
    int m_whoUsedRound;
    int m_coordination;
};

#endif