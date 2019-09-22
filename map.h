#ifndef RICHMAN_MAP_H
#define RICHMAN_MAP_H

#include "common.h"

// 给map每个点初始化
void initMap(GAME*);
void initComponent(GAME*);
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
// 显示帮助菜单
void showHelp();

void startAnimation();
// 控制游戏终端
void termctl(char *);
// 控制键盘响应
int set_disp_mode(int fd,int option);
// 游戏结束动画
void endAnimation();
// 清除使用过的炸弹和路障
void clearBombOrBlock(GAME*);
// 游戏胜利之后的显示
void showGameOver();

#endif
