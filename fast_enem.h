#include "Enemy.h"

class FastEnemy : public Enemy
{
public:
    FastEnemy(int x, int y);
    ~FastEnemy();
    virtual void UpdatePos();
    virtual void TryUpdatePos();
    virtual void BackToOldPos();
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
    int m_disparityX;
    int m_disparityY;
    int m_whoUsedRound;
    int m_xOrY;
    bool m_decision;
};
