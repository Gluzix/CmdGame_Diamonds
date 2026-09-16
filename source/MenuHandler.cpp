#include "MenuHandler.h"
#include <conio.h>
#include <cstdlib>
#include <Windows.h>

namespace
{
    constexpr int firstArrowPrefix = 0;
    constexpr int secondArrowPrefix = 224;
    constexpr int upArrowCode = 72;
    constexpr int downArrowCode = 80;
    constexpr int enterCode = 13;
}

GameStatus MenuHandler::run()
{
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    menu.show(static_cast<int>(status));

    while (true)
    {
        const int key = _getch();

        if (key == firstArrowPrefix || key == secondArrowPrefix) {
            const int arrow = _getch();

            if (arrow == upArrowCode) {
                upArrowClicked();
            }
            else if (arrow == downArrowCode) {
                downArrowClicked();
            }
            else {
                continue;
            }

            menu.show(static_cast<int>(status));
        }
        else if (key == enterCode) {
            system("cls");
            return status;
        }
    }
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
