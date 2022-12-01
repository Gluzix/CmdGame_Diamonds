#include "MenuHandler.h"
#include <conio.h>
#include <Windows.h>

MenuHandler::MenuHandler()
{

}

GameStatus MenuHandler::run()
{
    GameStatus gameStatus = GameStatus::Start;
    while (1)
    {
        menu.show(static_cast<int>(gameStatus));        
        int menuIndex = static_cast<int>(gameStatus);

        if (GetAsyncKeyState(VK_UP))
        {
            if (menuIndex > 0) {
                menuIndex--;
            } else {
                menuIndex = 2;
            }
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            if (menuIndex < 2) {
                menuIndex++;
            }
            else { 
                menuIndex = 0;
            }
        }
        else if (GetAsyncKeyState(VK_RETURN))
        {
            system("cls");
            return gameStatus;
        }

        gameStatus = static_cast<GameStatus>(menuIndex);

        getch();
        system("cls");
    }
	return GameStatus::Exit;
}
