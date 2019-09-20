//
// Created by 周瑞松 on 2019/9/14.
//

#ifndef RICHMAN_JUDGE_H
#define RICHMAN_JUDGE_H

#include "common.h"
#include "building.h"

int judgeMoney(int);
char* judgePlayer(char*);
char judgeYN(char*);
void nextIndex(GAME*);
void changePlayerStatus(GAME*);
#endif //RICHMAN_JUDGE_H
