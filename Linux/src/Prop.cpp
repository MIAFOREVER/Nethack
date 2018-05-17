#include"Prop.h"
#include<cstdlib>
#include<ctime>
#include"define.h"
#include"data.h"
bool Prop::inside(int x, int y)
{
	if (x >= 0 && x <= MAX_X && y >= 0 && y <= MAX_Y)
		return true;
	else
		return false;
}
void Prop::produceProp()
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