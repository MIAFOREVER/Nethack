#include"Transport.h"
#include<cstdlib>
#include<ctime>
#include"define.h"
#include"data.h"
void Transport::produceTranport()
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
void Transport::produceNecklace()
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
