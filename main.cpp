#include <iostream>
#include "Menu.h"
#include <Windows.h>

int main()
{
	Menu menu;
	menu.show(0);
	Sleep(2000);
	menu.show(1);
	Sleep(2000);
	menu.show(2);

	return 0;
}
