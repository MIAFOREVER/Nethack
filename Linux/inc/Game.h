#pragma once
#include"define.h"
#include"data.h"
#include"Map.h"
#include"Prop.h"
#include"Monster.h"
#include"Actor.h"
#include"Transport.h"
class Game
{
    public:
    Game(); 
    ~Game();
    void produceMap();
    void run();
    private:
    Map* map;
    Prop* prop;
    Monster* monster;
    Actor* actor;
    Transport* transport;
};