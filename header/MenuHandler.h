#pragma once

#include "Menu.h"

// The values are the index Menu::show() expects, so they must follow the on-screen order.
enum class GameStatus : int {
	Start = 0,
	About = 1,
	Exit = 2
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

