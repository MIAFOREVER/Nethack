#include"Monster.h"
#include<cstdlib>
#include<ctime>
#include"define.h"
#include"data.h"
void Monster::produceMonster()
{
	srand(time(0));
	int monsterNum = 0;
	while (monsterNum<MONSTERNUM)
	{
		int x = rand() % (100);
		int y = rand() % (100);
		if (map[x][y] == 3&&inside(x,y))
		{
			map[x][y] = 5;
			monster_x[monsterNum] = x;
			monster_y[monsterNum] = y;
			monster_HP[monsterNum] = 100;
			monster_attack[monsterNum] = 30;
			monster_alive[monsterNum] = true;
			monsterNum++;
		}

	}
}
void Monster::monsterMove()
{
	for (int i = 0; i < MONSTERNUM; i++)
	{
		int x = monster_x[i];
		int y = monster_y[i];
		if (monster_alive[i])
		{
			if (rand() % (2))
			{
				x++;
			}
			else
			{
				x--;
			}
			if (rand() % (2))
			{
				if (rand() % (2))
				{
					y++;
				}
				else
				{
					y--;
				}
			}
		}
		if (map[x][y] == 3&& monster_alive[i])
		{
			map[monster_x[i]][monster_y[i]] = 3;
			map[x][y] = 5;
			monster_x[i] = x;
			monster_y[i] = y;

			
		}
	}
}
bool Monster::inside(int x, int y)
{
	if (x >= 0 && x <= MAX_X && y >= 0 && y <= MAX_Y)
		return true;
	else
		return false;
}