#ifndef PUNCTATION_H
#define PUNCTATION_H


class punctation
{
    int points;
    public:
    punctation(int pkt):points(pkt){}
    void update_points();
    void show_points();
    int return_of_players_points();
};

#endif // PUNCTATION_H
