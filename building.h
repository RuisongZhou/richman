#ifndef RICHMAN_BUILDING_H
#define RICHMAN_BUILDING_H 

#include <stdio.h>
#include "common.h"

// 进入医院
void getin_hospital(GAME*);

// 进入监狱
void getin_police(GAME*);

// 进入礼品屋
void getin_gifthouse(GAME*);

// 进入道具屋
void getin_toolhouse(GAME*);

//进入土地
void getin_house(GAME *);

//进入魔法屋
void getin_magic_house(GAME *);

// 获取读入的函数
char getInput();

// 获取玩家名称
char *getName(char);

#endif 
