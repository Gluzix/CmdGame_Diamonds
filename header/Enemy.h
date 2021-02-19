#ifndef ENEMY
#define ENEMY

class Enemy
{
public:
    Enemy();
    virtual ~Enemy();
    virtual void UpdatePosition() = 0;
    virtual void UpdateConsoleCoordinates() = 0;
    virtual void BackToOldPosition() = 0;
    virtual bool IsPlayerNear(int, int) = 0;
    virtual int GetX() = 0;
    virtual int GetY() = 0;
};

#endif