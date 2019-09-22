//
// Created by 周瑞松 on 2019/9/14.
//

#ifndef RICHMAN_ACTION_H
#define RICHMAN_ACTION_H

#include "map.h"
#include "common.h"
#include "judge.h"
#include "initialize.h"

bool buyHouse(GAME*);
bool sellHouse(GAME* , int);
bool updateHouse(GAME* );
bool payfees(GAME* );
void bankrupt(GAME *g);

bool getPoints(GAME*);
bool setBomb(GAME *g, int dist);
bool setBlock(GAME *g, int dist);
bool setRobot(GAME *g);
void gameOver();

#endif //RICHMAN_ACTION_H
