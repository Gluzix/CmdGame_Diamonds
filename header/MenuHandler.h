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
	GameStatus run();

private:
	void upArrowClicked();
	void downArrowClicked();

	Menu menu;
	GameStatus status {GameStatus::Start};
};

