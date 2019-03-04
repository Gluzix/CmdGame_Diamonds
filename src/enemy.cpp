#include "enemy.h"
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <time.h>
using namespace std;
//plik zawierajacy metody dla klasy Enemy, ale klasa jest virtual, wiec nie zawiera cial zadnych metod, klasy pochodne
//beda te funckje przeciazac
enemy::enemy()
{

}
enemy::~enemy()
{

}
int enemy::return_pos_x()
{
return 0;
}
int enemy::return_pos_y()
{
return 0;
}
void enemy::return_to_old_pos()
{

}
void enemy::try_update_pos()
{

}
void enemy::update_pos()
{

}
bool enemy::check_if_player_is_near(int x, int y)
{

}
