#pragma once
class Map
{
public:
	Map();
	~Map();
	void run();
	void produceMainMap();
	void produceLink();
	void produceLinkOld();
	void produceBlock();
	void actorControl();
	void produceRandomMap();
	void printMap();
	void monsterMove();
	void printActor();
	bool inside(int x, int y);
	void printGameOver();
	void printGameVictor();
};
