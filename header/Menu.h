#pragma once

#include <string>
#include <vector>
#include "FileReader.h"

class Menu
{
public:
    Menu();
    Menu(const Menu& menu) = delete;

    void show(int index) const;

private:
    void showReadMenuOnScreen() const;
    void chooseStart() const;
    void chooseAbout() const;
    void chooseExit() const;

    FileReader fileReader{"resources/Logo.txt"};
};