//
// Created by 周瑞松 on 2019/9/14.
//

#ifndef RICHMAN_INITIALIZE_H
#define RICHMAN_INITIALIZE_H

#include "common.h"

void initialize(GAME *game_pointer, int money, char*);
void init_map(MAP_INFOMATION *map);
void init_player(PLAYER *player, int id, int money, char symbol);
void init_reset(GAME *g, char *);
// 关闭ctrl+c
void pleaseQuit(int);
// 退出游戏的函数
void quit();
// 设置回合数时根据回合数修改玩家状态
void changeStatusWithSetRounds(GAME*, int);
void ctrlC(int);

#endif //RICHMAN_INITIALIZE_H
