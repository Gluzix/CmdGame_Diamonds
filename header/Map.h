#include <string>
#include <vector>
#include <FileReader.h>
#include "Coordinates.h"


class Map
{
    public:
        Map(const FileReader &reader);
        void drawMap();
        bool isObstacleForEnemy(int x, int y, int i);
        bool isObstacleForPlayer(int x, int y);

        const Coordinates& getSlowerEnemyCoords(int index);
        const Coordinates& getFasterEnemyCoords(int index);
        const Coordinates& getPlayerCoords();

        bool hasPlayerTookDiamond(const Coordinates& coords);
        bool hasPlayerSwitchedGate(const Coordinates& coords);
        bool isGameLost(const Coordinates &coords);
        int getPoints();
        void removeBarriers();

        bool hasPlayerFinished(const Coordinates& coords);

private:
    void drawAsteriks();
    void drawDollar();
    void drawAmpersand();
    void drawHashtag();
    void drawCommercialAt();
    void drawCaret();

    std::vector<std::string> startString{};
    std::vector<Coordinates> fasterEnemiesPos{};
    std::vector<Coordinates> slowerEnemiesPos{};
    std::vector<Coordinates> barrierPos{};

    Coordinates playerPos{ 0, 0 };

    int points{0};

    FileReader& fileReader;
};
