#pragma once

#include "Enemy.h"
#include "Map.h"
#include <string>
#include <vector>
#include <FileReader.h>
#include <memory>

class GameHandler
{
public:
	void run();

private:
	void prepareEnemies();
	void moveEnemies(const Coordinates& playerCoordinates);
	bool isPlayerCaught(const Coordinates& playerCoordinates) const;
	void showEndScreen(const std::string& pathToFile) const;

	std::vector<std::unique_ptr<Enemy>> enemies;

	Map map;
};
