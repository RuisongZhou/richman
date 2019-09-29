//
// Created by 周瑞松 on 2019/9/14.
//
#include "action.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

/*
    by 周瑞松
    function：买房子
*/
_Bool buyHouse(GAME* g)
{
    PLAYER *p = &(g->players[g->playerIndex]);
    LOCATION *loc = &(g->map.local[p->index]);
    int liftMoney = p->money - loc->cost;
    if(loc->belong != -1 || liftMoney < 0){
        //printf("不能买");
        return 0;
    }
    p->money = liftMoney;
    p->house_index[p->house_num] = p->index;
    p->house_num++;
    loc->belong = p->id;
    loc->level = 0;
    return 1;
}

/*
    by  郭一兴
    function：卖房子
*/
_Bool sellHouse(GAME* g, int sell_house_index)
{
    if (sell_house_index < MAP_SIZE && sell_house_index > 0) {
        PLAYER *p = &(g->players[g->playerIndex]);
        int i, j;
        for (i = 0; i < p->house_num; ++i) {
            if (p->house_index[i] == sell_house_index) {
                LOCATION *sell_house = &(g->map.local[sell_house_index]);
                int cash = (sell_house->cost) * (sell_house->level+1) * 2;
                sell_house->belong = -1;
                sell_house->level = 0;

                //清除卖家的house_index对应的房子相对位置数组元素
                p->house_num -= 1;
                for(j = i; j < p->house_num; ++j){
                    p->house_index[j]=p->house_index[j+1];
                }
                if (!(p->playerStatus)) {
                    p->money += cash;
                    char *message = NULL;
                    message = (char*)calloc(100, sizeof(char));
                    sprintf(message, "你成功卖出了自己的房子，现在持有的现金是：%d", p->money);
                    showMessage(message);
                    free(message);
                }
                return 1;
            }
        }
    }
    return 0;
}

/*
    by  郭一兴
    function：升级房子
*/
_Bool updateHouse(GAME* g)
{
    PLAYER *p = &(g->players[g->playerIndex]);
    LOCATION *loc = &(g->map.local[p->index]);
    if(loc->attr == 1){
        int cash = loc->cost;
        if(p->money < cash) {
            return 0;
        }
        p->money -= cash;
        loc->level ++;
        return 1;
    } else {
        return 0;
    }
}

/*
    by  郭一兴
    function：支付租金
*/
_Bool payfees(GAME* g) {
    int i, tenant, host, cost;

    tenant = g->playerIndex;
    host = g->map.local[g->players[g->playerIndex].index].belong - 1;
    
    cost = (g->map.local[g->players[tenant].index].level + 1) * g->map.local[g->players[tenant].index].cost / 2;
    g->players[host].money += cost;
    g->players[tenant].money -= cost;

    if (g->players[tenant].money >= 0) {
        return 1;
    }

    return 0;
}

/*
    by  郭一兴
    function：走到矿地，获得点数
*/
_Bool getPoints(GAME* g)
{
    PLAYER *p = &(g->players[g->playerIndex]);
    LOCATION *loc = &(g->map.local[p->index]);
    if(loc->attr == 7){
        int point = loc->cost;
        p->point+=point;
        return 1;
    } else {
        return 0;
    }
}

/*
    by 郭一兴
    function: 布置炸弹
*/
_Bool setBomb(GAME *g, int dist)
{
    PLAYER *p = &(g->players[g->playerIndex]);
    int locIndex = p->index + dist;
    if(locIndex<0){
        locIndex += MAP_SIZE;
    } else if(locIndex >= MAP_SIZE){
        locIndex -= MAP_SIZE;
    }
    LOCATION *loc = &(g->map.local[locIndex]);
    if(p->gift[0]>0 && loc->bomb==false && loc->block==false){
        loc->bomb = true;
        p->gift[0]--;
        return 1;
    }
    else {
        return 0;
    }
}

/*
    by 郭一兴
    function: 布置路障
*/
_Bool setBlock(GAME *g, int dist)
{
    PLAYER *p = &(g->players[g->playerIndex]);
    int locIndex = p->index + dist;
    if(locIndex<0){
        locIndex += MAP_SIZE;
    } else if(locIndex >= MAP_SIZE){
        locIndex -= MAP_SIZE;
    }
    LOCATION *loc = &(g->map.local[locIndex]);
    if(p->gift[1]>0 && !(loc->bomb) && !(loc->block)){
        loc->block = 1;
        p->gift[1]--;
        return 1;
    }
    else {
        return 0;
    }
}

/*
    by 郭一兴
    function: 放置机器人
*/
_Bool setRobot(GAME *g)
{
    PLAYER *p = &(g->players[g->playerIndex]);
    if(p->gift[2]>0){
        int i;
        LOCATION *loc;
        for(i=1;i<=10;i++){
            loc = &(g->map.local[(p->index+i)%MAP_SIZE]);
            loc->block = loc->bomb = 0;
        }
        p->gift[2]--;
        return 1;
    } else {
        return 0;
    }
}

void bankrupt(GAME *g){
    int i;
    g->players[g->playerIndex].playerStatus = 1;

    for (i = 0; i < g->players[g->playerIndex].house_num; ++i) {
        int index;
        index = g->players[g->playerIndex].house_index[i];
        g->map.local[index].belong = -1;
        g->map.local[index].level = 0;
        g->players[g->playerIndex].house_index[i] = 0;
    }
    g->players[g->playerIndex].gift[0] = 0;
    g->players[g->playerIndex].gift[1] = 0;
    g->players[g->playerIndex].gift[2] = 0;
    g->players[g->playerIndex].point = 0;
    g->players[g->playerIndex].house_num = 0;
    g->player_less_num -= 1;
    g->players[g->playerIndex].money = 0;
    g->players[g->playerIndex].hospital_days = 0;
    g->players[g->playerIndex].police_days = 0;
    g->players[g->playerIndex].bless_days = 0;
    g->players[g->playerIndex].magic_time = 0;
}

// 游戏结束逻辑
void gameOver(GAME *g) {
    if (g->player_less_num == 1) {
        char message[100];
        sprintf(message, "恭喜%s获得游戏胜利，乌拉～", getName(g->players[g->playerIndex].name));
        showSystemMessage(message);
        sleep(2);
        showGameOver();
        quit();
    }
}
