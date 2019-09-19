#ifndef RICHMAN_MAP_H
#define RICHMAN_MAP_H

#include "common.h"

// 给map每个点初始化
void initMap(GAME*);
// 绘制地图以及玩家输入模块
void drawMap(GAME*);
// 显示提示信息
void showMessage(char*);
// 显示玩家信息
void showQuery(GAME*);
// 显示系统提示
void showSystemMessage(char*);
// 显示游戏回合数
void showRound(int);

#endif
