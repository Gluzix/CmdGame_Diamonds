#include "Enemy.h"
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <time.h>

//plik zawierajacy metody dla klasy Enemy, ale klasa jest virtual, wiec nie zawiera cial zadnych metod, klasy pochodne
//beda te funckje przeciazac

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

int Enemy::GetX()
{
	return 0;
}

int Enemy::GetY()
{
	return 0;
}

void Enemy::BackToOldPos()
{

}

void Enemy::TryUpdatePos()
{

}

void Enemy::UpdatePos()
{

}

bool Enemy::IsPlayerNear(int x, int y)
{

}
