#pragma once
class Map
{
#define MAX_X 100   //the length of map_x
#define MAX_Y 25    //the length of map_y
#define MAX_R 8     //the size of room_max
#define MIN_R 4     //th size of room_min
#define MAPNUM 8    //the size of room number
#define MONSTERNUM 10  //monster number
#define PROPNUM 5      //prop number
#define WARFOG 10      //size of war fog 
#define LAYER 5        //the layer
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
	void produceTranport();
	void hit(int x,int y);
	bool inside(int x, int y);
	int findMonster(int x, int y);
	int findProp(int x, int y);
	void printGameOver();
	void printGameVoctor();
private:
	int map[MAX_X][MAX_Y];//cout<<symbol[map[x][y]];
	char symbol[30] = { " @X.#MEI|-0123456789ST" };
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
	bool alive;
	int layer;
	int transport_x;
	int transport_y;
};