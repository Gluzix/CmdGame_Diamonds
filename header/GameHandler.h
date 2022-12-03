#pragma once

#include "Enemy.h"
#include "Map.h"
#include <vector>
#include <FileReader.h>
#include <memory>

class GameHandler
{
public:
	GameHandler();

	void run();

private:
	void prepareEnemies();

	// TODO: try std::reference_wrapper?
	std::vector<std::shared_ptr<Enemy>> enemies;

	Map map;
};
