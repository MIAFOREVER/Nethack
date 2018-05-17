#include"Game.h"
#include"Map.h"
#include"Prop.h"
#include"Monster.h"
#include"Actor.h"
#include"Transport.h"
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include <termio.h>
#include <assert.h>
#include<string.h>
#include"define.h"
#include"data.h"
Game::Game()
{
    map=new Map;
    prop=new Prop;
    monster=new Monster;
    actor=new Actor;
    transport=new Transport;
}
Game::~Game()
{
    delete map;
    delete prop;
    delete monster;
    delete actor;
    delete transport;
}
int getch(void)
{
        int c=0;
        struct termios org_opts, new_opts;
        int res=0;
        res=tcgetattr(STDIN_FILENO, &org_opts);
        assert(res==0);
        memcpy(&new_opts, &org_opts, sizeof(new_opts));
        new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
        c=getchar();
        res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);assert(res==0);
        return c;
}
void *threadKeyWord(void* ptr)
{
	while (1)
	{
		 keyBroadInput=getch();
	}
	return 0;
}
void Game::produceMap()
{
    map->produceMainMap();
	map->produceLink();
	map->produceBlock();
	monster->produceMonster();
	prop->produceProp();
	actor->produceActor();
	if (layer < LAYER)
		transport->produceTranport();
	else
		transport->produceNecklace();
}
void Game::run()
{
    srand(time(0));
	pthread_t id;
	int ret=pthread_create(&id,NULL,threadKeyWord,NULL);
	for (int i = 0; i < LAYER; i++)
	{
		produceMap();
		while (mainLoop)
		{
			map->printMap();
			map->printActor();
			sleep(1);
			actor->actorControl();
			monster->monsterMove();
			system("clear");
		}
		if (alive == false)
			map->printGameOver();
		if (gameLoop)
			map->printGameVictor();
		mainLoop = true;
		layer++;
	}
}