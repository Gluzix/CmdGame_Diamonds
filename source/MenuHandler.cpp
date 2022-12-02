#include "MenuHandler.h"
#include <conio.h>
#include <Windows.h>

MenuHandler::MenuHandler()
{

}

GameStatus MenuHandler::run()
{
    while (1)
    {
        menu.show(static_cast<int>(status));

        if (GetAsyncKeyState(VK_UP)) {
            upArrowClicked();
        }
        else if (GetAsyncKeyState(VK_DOWN)) {
            downArrowClicked();
        }
        else if (GetAsyncKeyState(VK_RETURN))
        {
            system("cls");
            return status;
        }

        getch();
        system("cls");
    }
	return GameStatus::Exit;
}

void MenuHandler::upArrowClicked()
{
    if (status == GameStatus::Exit) {
        status = GameStatus::About;
    }
    else if (status == GameStatus::About) {
        status = GameStatus::Start;
    } else {
        status = GameStatus::Exit;
    }
}

void MenuHandler::downArrowClicked()
{
    if (status == GameStatus::Start) {
        status = GameStatus::About;
    }
    else if (status == GameStatus::About) {
        status = GameStatus::Exit;
    }
    else {
        status = GameStatus::Start;
    }
}
