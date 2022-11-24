#pragma once

class Punctation
{
public:
    Punctation(int maxPunctation);

    void update();
    void show();
    int get();

private:
    int punctation{0};
    int maxPunctation;
};
