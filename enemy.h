#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

class Enemy
{
public:
    Enemy();
    virtual ~Enemy();
    virtual void UpdatePos();
    virtual void TryUpdatePos();
    virtual void BackToOldPos();
    virtual bool IsPlayerNear(int, int);
    virtual int GetX();
    virtual int GetY();
};
