#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

class Enemy
{
public:
    Enemy();
    virtual ~Enemy();
    virtual void UpdatePosition();
    virtual void UpdateConsoleCoordinates();
    virtual void BackToOldPosition();
    virtual bool IsPlayerNear(int, int);
    virtual int GetX();
    virtual int GetY();
};
