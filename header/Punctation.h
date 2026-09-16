#pragma once

class Punctation
{
public:
    Punctation(int maxPunctation, int row);

    void update();
    void show();
    int get();

private:
    int punctation{0};
    int maxPunctation;
    int row;
};
