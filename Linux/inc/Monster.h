#pragma once
#include"define.h"
#include"data.h"
class Monster
{
    public:
	void produceMonster();
	void monsterMove();
	bool inside(int x, int y);
};