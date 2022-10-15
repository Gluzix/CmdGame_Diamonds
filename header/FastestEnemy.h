class FastestEnemy
{
public:
    FastestEnemy(int x, int y, int hisway);
    virtual void UpdatePosition();
    virtual void UpdateConsoleCoordinates();
    virtual void BackToOldPosition();
    virtual int GetX();
    virtual int GetY();
private:
    short m_posY;
    short m_oldPosY;
    short m_posX;
    short m_oldPosX;
    int m_hisWay;
    int m_counter;
    int m_counterSecond;
};
