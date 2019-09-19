#ifndef RICHMAN_TOOLS_H
#define RICHMAN_TOOLS_H

#include <stdio.h>
#include "map.h"
#include "common.h"

// 设置障碍
void set_block(int, int, GAME *);

// 设置炸弹
void set_bomb(int, int, GAME*);

// 设置机器人
void set_robot(int, GAME*);

#endif 
