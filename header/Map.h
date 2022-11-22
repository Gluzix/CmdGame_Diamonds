#include <string>
#include <vector>
#include <FileReader.h>

struct Coordinates {

    Coordinates(int x, int y) {
        this->x = x;
        this->y = y;
    }

    Coordinates() {
        this->x = -1;
        this->y = -1;
    }

    Coordinates operator =(const Coordinates& coords) {
        return Coordinates(coords.x, coords.y);
    }

    bool operator ==(const Coordinates& coords) {
        return this->x == coords.x && this->y == coords.y;
    }

    int x;
    int y;
};

bool operator ==(const Coordinates& coords1, const Coordinates& coords2) {
    return coords1.x == coords2.x && coords1.y == coords2.y;
}

class Map
{
    public:
        Map();
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
        std::vector<std::string> startString;
        std::vector<Coordinates> fasterEnemiesPos;
        std::vector<Coordinates> slowerEnemiesPos;
        std::vector<Coordinates> barrierPos;

        Coordinates playerPos;

        int points;

        FileReader fileReader{ "resources/Map.txt" };

        void drawAsteriks();
        void drawDollar();
        void drawAmpersand();
        void drawHashtag();
        void drawCommercialAt();
        void drawCaret();
};
