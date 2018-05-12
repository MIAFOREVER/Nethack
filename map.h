#pragma once
class Map
{
#define MAX_X 100
#define MAX_Y 25
#define MAX_R 8
#define MIN_R 4
#define MAPNUM 8
#define MONSTERNUM 10
#define PROPNUM 5
#define WARFOG 10

public:
	void run();
	void actorControl();
	void produceRandomMap();
	void printMap();
	void monsterMove();
	void printActor();
	Map();
	~Map();
private:
	void produceMainMap();
	void produceLink();
	void produceLinkOld();
	void produceBlock();
	void produceMonster();
	void produceProp();
	void produceActor();
	void produceNecklace();
	void hit(int x,int y);
	bool inside(int x, int y);
	int findMonster(int x, int y);
	int findProp(int x, int y);
	void printGameOver();
	void printGameVoctor();
private:
	int map[MAX_X][MAX_Y];//cout<<symbol[map[x][y]];
	char symbol[30] = { " @X.#MEI|-0123456789S" };
	int x[MAPNUM], y[MAPNUM], r[MAPNUM];
	int monster_num = MONSTERNUM;
	int monster_x[MONSTERNUM];
	int monster_y[MONSTERNUM];
	int monster_HP[MONSTERNUM];
	int monster_attack[MONSTERNUM];
	int monster_alive[MONSTERNUM];
	int prop_num = PROPNUM;
	int prop_attack[PROPNUM];
	int prop_x[PROPNUM];
	int prop_y[PROPNUM];
	int actor_HP;
	int actor_Money;
	int actor_x;
	int actor_y;
	int actor_attack;
	int necklice_x;
	int necklice_y;
	bool mainLoop;
	bool gameLoop;
};