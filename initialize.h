//
// Created by 周瑞松 on 2019/9/14.
//

#ifndef RICHMAN_INITIALIZE_H
#define RICHMAN_INITIALIZE_H

#include "common.h"

void initialize(GAME *game_pointer, int money, char*);
void init_map(MAP_INFOMATION *map);
void init_player(PLAYER *player, int id, int money);
void init_reset(GAME *g, char *);
#endif //RICHMAN_INITIALIZE_H
