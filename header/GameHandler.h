#pragma once

#include "Enemy.h"
#include "Map.h"
#include <vector>
#include <FileReader.h>

class GameHandler
{
public:
	GameHandler();

	void run();
	void prepareEnemies();

private:
	std::vector<Enemy> fastEnemies;
	std::vector<Enemy> slowEnemies;

	const FileReader& fileReader;

	Map map;
};
