#pragma once
#include"define.h"
#include"data.h"
class Actor
{
    public:
    void hit(int x,int y);
    void produceActor();
    void actorControl();
    int findMonster(int x, int y);
	int findProp(int x, int y);
    bool inside(int x, int y);
};
