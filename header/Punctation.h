#pragma once

class Punctation
{
public:
    Punctation(int maxPunctation, int row);

    void update();
    void show() const;
    int get() const;

private:
    int punctation{0};
    int maxPunctation;
    int row;
};
