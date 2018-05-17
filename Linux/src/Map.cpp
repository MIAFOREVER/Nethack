#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<pthread.h>
#include"Map.h"
#include<stdio.h>
#include<fstream>
#include<unistd.h>
#include <termio.h>
#include <assert.h>
#include<string.h>
#include"define.h"
#include"data.h"
using namespace std;

int distance(int x1, int y1, int x2, int y2)
{
	int distance_x;
	if (x2 > x1)
		distance_x = x2 - x1;
	else
		distance_x = x1 - x2;
	int distance_y;
	if (y2 > y1)
		distance_y = y2 - y1;
	else
		distance_y = y1 - y2;
	return distance_x + distance_y;
}

bool Map::inside(int x, int y)
{
	if (x >= 0 && x <= MAX_X && y >= 0 && y <= MAX_Y)
		return true;
	else
		return false;
}
Map::Map()
{
	for (int i = 0; i < MAX_X; i++)
		for (int j = 0; j < MAX_Y; j++)
			map[i][j] = 0;
	for (int i = 0; i < MAX_X; i++)
		for (int j = 0; j < MAX_Y; j++)
			mapWarFog[i][j] = false;
	actor_Money = 0;
	actor_attack = 0;
	layer = 1;
	mainLoop = true;
	gameLoop = false;
	alive = true;
}
Map::~Map()
{

}
void Map::produceLink()
{
	for (int i = 0; i < MAPNUM - 1; i++)
	{
		int xtemp=x[i];
		int ytemp=y[i];
		int dis = distance(x[i], y[i], x[i + 1], y[i + 1]);
		while (distance(xtemp, ytemp, x[i + 1], y[i + 1])>0)
		{
			int direction = rand() % (4);
			int x1 = xtemp;
			int y1 = ytemp;
			//cout << direction << endl;
			if (direction == 0)
				x1++;
			else if (direction == 1)
				x1--;
			else if (direction == 2)
				y1++;
			else if (direction == 3)
				y1--;
			if (distance(x1, y1, x[i + 1], y[i + 1]) < distance(xtemp, ytemp, x[i + 1], y[i + 1]))
			{
				xtemp = x1;
				ytemp = y1;
				if(map[x1][y1] != 3 && inside(x1, y1))
				map[x1][y1] = 4;
			}
		}
	}
}
void Map::produceBlock()
{
	for (int i = 0; i < MAX_X; i++)
	{
		for (int j = 0; j < MAX_Y; j++)
		{
			if (map[i][j] == 3)
			{
				if (map[i + 1][j] != 3 && map[i + 1][j] != 4 && inside(i, j))
					map[i + 1][j] = 8;
				if (map[i - 1][j] != 3 && map[i - 1][j] != 4 && inside(i, j))
					map[i - 1][j] = 8;
				if (map[i][j + 1] != 3 && map[i][j + 1] != 4 && inside(i, j))
					map[i][j + 1] = 9;
				if (map[i][j - 1] != 3 && map[i][j - 1] != 4 && inside(i, j))
					map[i][j - 1] = 9;
			}
		}
	}
}
void Map::produceMainMap()
{
	srand(time(0));
	for (int i = 0; i < MAPNUM; i++)
	{
		r[i] = rand() % (MAX_R - MIN_R+1)+MIN_R;
		int x1 = MAX_X - r[i], x2 = r[i];
		x[i] = rand() % (x1 - x2 + 1) + x2;
		int y1 = MAX_Y - r[i], y2 = r[i];
		y[i] = rand() % (y1 - y2 + 1) + y2;
		for (int j = x[i] - r[i]; j < x[i] + r[i]; j++)
		{
			for (int p = y[i] - r[i]; p < y[i] + r[i]; p++)
			{
				if (inside(j, p)&&map[j][p]<11)
					map[j][p] = 3;
			}
		}
	}
}
void Map::printMap()
{
	for (int y = 0; y < MAX_Y; y++)
	{
		for (int x = 0; x < MAX_X; x++)
		{
			if (map[x][y] >= 0 && map[x][y] <= 29 && inside(x, y))
			{
				if (distance(x, y, actor_x, actor_y) < 10)
					mapWarFog[x][y] = true;
				if(mapWarFog[x][y]||map[x][y]==21||map[x][y]==20)
					cout << symbol[map[x][y]];
				else
					cout << " ";
			}
		}
		cout << "\n";
	}
}
void Map::printActor()
{
	cout << "Actor HP: " << actor_HP << "   ATTACK: " << actor_attack << "   MONEY: " << actor_Money <<"   X: "<<actor_x<<"   Y: "<<actor_y<< endl;
	cout << "the number of layer:   " << layer << "  tranport_x: " << transport_x << "  tansport_y: " << transport_y<<"\n";
}
void Map::printGameOver()
{
	system("clear");
	cout << "GAME OVER,YOU ARE KILLED BY MONSTER!\n";
	sleep(5);
	exit(0);
}
void Map::printGameVictor()
{
	system("clear");
	cout << "YOU WIN !\n";
	sleep(5);
	exit(0);
}

