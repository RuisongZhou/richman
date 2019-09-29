//
// Created by 周瑞松 on 2019/9/14.
//

#ifndef RICHMAN_ACTION_H
#define RICHMAN_ACTION_H

#include "building.h"
#include "common.h"
#include "judge.h"
#include "initialize.h"

_Bool buyHouse(GAME*);
_Bool sellHouse(GAME*, int);
_Bool updateHouse(GAME*);
_Bool payfees(GAME*);
void bankrupt(GAME*);

_Bool getPoints(GAME*);
_Bool setBomb(GAME*, int);
_Bool setBlock(GAME*, int);
_Bool setRobot(GAME*);
void gameOver(GAME*);

#endif //RICHMAN_ACTION_H
