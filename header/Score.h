#pragma once

class Score
{
public:
    Score(int total, int row);

    void update();
    void show() const;
    int get() const;

private:
    int collected{0};
    int total;
    int row;
};
