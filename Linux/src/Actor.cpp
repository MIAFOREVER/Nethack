#include"Actor.h"
#include<cstdlib>
#include<ctime>
void Actor::hit(int x,int y)
{
    if (map[x][y] == 3||map[x][y]==4)
	{
		if (map[x][y] == 3)
		{
			map[actor_x][actor_y] = 3;
			map[x][y] = 1;
			actor_x = x;
			actor_y = y;
		}
		if (map[x][y] == 4)
		{
			map[actor_x][actor_y] = 4;
			map[x][y] = 1;
			actor_x = x;
			actor_y = y;
		}
	}
	if (map[x][y] == 8 || map[x][y] == 9)
	{
		//Do nothing,hit on the wall;
	}
	if (map[x][y] == 5)
	{
		int num = findMonster(x,y);
		if (actor_attack > monster_HP[num])
		{
			map[actor_x][actor_y] = 3;
			map[x][y] = 1;
			actor_x = x;
			actor_y = y;
			monster_alive[num] = false;
			actor_Money += 10;
		}
		else 
		{
			actor_HP -= monster_attack[num];
			monster_HP[num] -= actor_attack;
			if (actor_HP <= 0)
			{
				alive = false;
				mainLoop = false;
			}
		}
	}
	if (map[x][y] == 6)
	{
		int num = findProp(x, y);
		actor_attack += prop_attack[num];
		map[x][y] = 1;
		map[actor_x][actor_y] = 3;
		actor_x = x;
		actor_y = y;
	}
	if (map[x][y] == 20)
	{
		mainLoop = false;
		gameLoop = true;

	}
	if (map[x][y] == 21)
	{
		mainLoop = false;
		for (int i = 0; i < MAX_X; i++)
			for (int j = 0; j < MAX_Y; j++)
				mapWarFog[i][j] = false;
	}
}
void Actor::produceActor()
{
	srand(time(0));
	int x = 0;
	int y = 0;
	int i = 1;
	while (i)
	{
		x = rand() % MAX_X;
		y = rand() % MAX_Y;
		if (map[x][y] == 3)
		{
			map[x][y] = 1;
			actor_x = x;
			actor_y = y;
			actor_HP = 100;
			actor_Money += 0;
			actor_attack += 0;
			i--;
		}
	}
}
int Actor::findMonster(int x, int y)
{
	for (int i = 0; i < MONSTERNUM; i++)
	{
		if (monster_x[i] == x && monster_y[i] == y)
		{
			return i;
		}
	}
}
int Actor::findProp(int x, int y)
{
	for (int i = 0; i < PROPNUM; i++)
	{
		if (prop_x[i] == x && prop_y[i] == y)
		{
			return i;
		}
	}
}
bool Actor::inside(int x, int y)
{
	if (x >= 0 && x <= MAX_X && y >= 0 && y <= MAX_Y)
		return true;
	else
		return false;
}
void Actor::actorControl()
{
	switch (keyBroadInput)
	{
	    case 'a': 
	    {
			hit(actor_x - 1, actor_y);
			break;
	    }
		case 's':
		{
			hit(actor_x, actor_y + 1);
			break;
		}
		case 'd':
		{
			hit(actor_x + 1, actor_y);
			break;
		}
		case 'w':
		{
			hit(actor_x, actor_y - 1);
			break;
		}
		case 'q':
		{
			hit(actor_x - 1, actor_y - 1);
			break;
		}
		case 'e':
		{
			hit(actor_x + 1, actor_y-1);
			break;
		}
		case 'z':
		{
			hit(actor_x - 1, actor_y + 1);
			break;
		}
		case 'c':
		{
			hit(actor_x + 1, actor_y + 1);
			break;
		}
	}

	keyBroadInput = 0;
}