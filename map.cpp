#include<iostream>
#include<cstdlib>
#include<ctime>
#include<windows.h>
#include"map.h"
#include<conio.h>
#include<fstream>
using namespace std;
using std::cout;
using std::endl;
char keyBroadInput;
bool cls()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 };    /* here's where we'll home the cursor */
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
	DWORD dwConSize;                 /* number of character cells in the current buffer */

									 /* get the number of character cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return false;
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	/* fill the entire screen with blanks */
	if (!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten))
		return false;

	/* get the current text attribute */
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return false;

	/* now set the buffer's attributes accordingly */
	if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten))
		return false;

	/* put the cursor at (0, 0) */
	if (!SetConsoleCursorPosition(hConsole, coordScreen))
		return false;
}
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
int direction(int x1, int y1, int x2, int y2)
{
	if (x2 > x1&&y2 > y1)
		return 1;
	else if (x2 > x1&&y1 > y2)
		return 2;
	else if (x2<x1&&y2>y1)
		return 3;
	else if (x2 < x1&&y2 < y1)
		return 4;
	else
		return 0;
}
void Map::produceLinkOld()
{
	for (int p = 0; p < MAPNUM-1; p++)
	{
		int xdifference,ydifference;
		bool xswap=false, yswap=false;
		if (x[p + 1] > x[p])
		{
			xdifference = x[p + 1] - x[p];
		}
		else
		{
			xdifference = x[p] - x[p + 1];
			int temp = x[p + 1];
			x[p + 1] = x[p];
			x[p] = temp;
			xswap = true;
		}
		if (y[p + 1] > y[p])
		{
			ydifference = y[p + 1] - y[p];
		}
		else
		{
			ydifference = y[p] - y[p + 1];
			int temp = y[p + 1];
			y[p + 1] = y[p];
			y[p] = temp;
			yswap = true;
		}
		for (int i = 0; i < xdifference-1; i++)
		{
			if (map[i + x[p]][y[p]] != 3&&inside(i+x[p],y[p]))
				map[i + x[p]][y[p]] = 4;
		}
		for (int i = 0; i < ydifference-1; i++)
		{
			if (map[x[p + 1]][y[p] + i] != 3&&inside(x[p+1],y[p]+i))
				map[x[p + 1]][y[p] + i] = 4;
		}
		/*srand(time(0) + p);
		int distance = xdifference + ydifference - 2;
		int pos_x = x[p];
		int pos_y = y[p];
		int oddPos_x = pos_x;
		int oddPos_y = pos_y;
		while (distance)
		{
			if (rand() % (2))
				pos_x++;
			else
				pos_x--;
			if (rand() % 2)
				pos_y++;
			else
				pos_y--;
			if ((plus(oddPos_x- x[p+1]) + plus(oddPos_y - y[p+1])) > (plus(pos_x - x[p + 1]) + plus(pos_y - y[p + 1])))
			{
				oddPos_x = pos_x;
				oddPos_y = pos_y;
				if (map[pos_x][pos_y] != 3 && inside(pos_x, pos_y))
				{
					map[pos_x][pos_y] = 4;
				}
				distance--;
			}
		}*/
		if (xswap)
		{
			int temp = x[p + 1];
			x[p + 1] = x[p];
			x[p] = temp;
		}
		if (yswap)
		{
			int temp = y[p + 1];
			y[p + 1] = y[p];
			y[p] = temp;
		}
	}
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
void Map::produceRandomMap()
{
	produceMainMap();
	produceLink();
	produceBlock();
	produceMonster();
	produceProp();
	produceActor();
	if (layer < LAYER)
		produceTranport();
	else
		produceNecklace();
}
void Map::produceMonster()
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
void Map::produceProp()
{
	srand(time(0));
	int propNum = PROPNUM;
	while (propNum)
	{
		int x = rand() % (100);
		int y = rand() % (100);
		if (map[x][y] == 3 && inside(x, y))
		{
			map[x][y] = 6;
			propNum--;
			prop_attack[propNum] = rand() % (50) + 50;
			prop_x[propNum] = x;
			prop_y[propNum] = y;
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
				//Õ½ÕùÃÔÎíµÄÅÐ¶Ï
				if (distance(x, y, actor_x, actor_y) < 10)
					cout << symbol[map[x][y]];
				else
					cout << " ";
			}
		}
		cout << "\n";
	}
}
void Map::produceActor()
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
DWORD WINAPI ThreadKeyWord(LPVOID pM)
{
	while (1)
	{
		keyBroadInput = _getch();
	}
	return 0;
}
void Map::actorControl()
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
int Map::findMonster(int x, int y)
{
	for (int i = 0; i < MONSTERNUM; i++)
	{
		if (monster_x[i] == x && monster_y[i] == y)
		{
			return i;
		}
	}
}
int Map::findProp(int x, int y)
{
	for (int i = 0; i < PROPNUM; i++)
	{
		if (prop_x[i] == x && prop_y[i] == y)
		{
			return i;
		}
	}
}
void Map::hit(int x, int y)
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
	}
}
void Map::produceTranport()
{
	int x = 0;
	int y = 0;
	int i = 1;
	while (i)
	{
		x = rand() % MAX_X;
		y = rand() % MAX_Y;
		if (map[x][y] == 3)
		{
			transport_x = x;
			transport_y = y;
			map[x][y] = 21;
			i--;
		}
	}
}
void Map::produceNecklace()
{
	int x = 0;
	int y = 0;
	int i = 1;
	while (i)
	{
		x = rand() % MAX_X;
		y = rand() % MAX_Y;
		if (map[x][y] == 3)
		{
			necklice_x = x;
			necklice_y = y;
			map[x][y] = 20;
			i--;
		}
	}
}
void Map::monsterMove()
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
void Map::printActor()
{
	cout << "Actor HP: " << actor_HP << "   ATTACK: " << actor_attack << "   MONEY: " << actor_Money <<"   X: "<<actor_x<<"   Y: "<<actor_y<< endl;
	cout << "the number of layer:   " << layer << "  tranport_x: " << transport_x << "  tansport_y: " << transport_y;
}
void Map::printGameOver()
{
	system("cls");
	cout << "GAME OVER,YOU ARE KILLED BY MONSTER!\n";
	Sleep(5000);
	exit(0);
}
void Map::printGameVoctor()
{
	system("cls");
	cout << "YOU WIN !\n";
	Sleep(5000);
	exit(0);
}
void Map::run()
{
	srand(time(0));
	HANDLE handle = CreateThread(NULL, 0, ThreadKeyWord, NULL, 0, NULL);
	for (int i = 0; i < LAYER; i++)
	{
		produceRandomMap();
		while (mainLoop)
		{
			printMap();
			printActor();
			Sleep(500);
			actorControl();
			monsterMove();
			cls();
		}
		if (alive == false)
			printGameOver();
		if (gameLoop)
			printGameVoctor();
		mainLoop = true;
		layer++;
	}
}