#pragma once

#include "Menu.h"

enum class GameStatus : int {
	Start = 0,
	Exit = 1,
	About = 2
};

class MenuHandler
{
public:
	MenuHandler();
	GameStatus run();

private:
	Menu menu;
};

