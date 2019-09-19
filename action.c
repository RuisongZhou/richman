//
// Created by 周瑞松 on 2019/9/14.
//
#include "action.h"

/*
    by 周瑞松
    function：买房子
*/
bool buyHouse(GAME* g)
{
    PLAYER *p = &(g->players[g->playerIndex]);
    LOCATION *loc = &(g->map.local[p->index]);
    int liftMoney = p->money - loc->cost;
    if(liftMoney < 0){
        //printf("不能买");
        return false;
    }
    p->money = liftMoney;
    p->house_index[p->house_num] = p->index;
    p->house_num++;
    loc->belong = p->id;
    loc->level = 0;
    return true;
}

/*
    by  郭一兴
    function：卖房子
*/
bool sellHouse(GAME* g,int sell_house_index)
{
    PLAYER *p = &(g->players[g->playerIndex]);
    int i,j;
    for(i=0;i<p->house_num;i++){
        if(p->house_index[i]==sell_house_index){
            LOCATION *sell_house = &(g->map.local[sell_house_index]);
            int cash = (sell_house->cost) * (sell_house->level+1) * 2;
            p->money+=cash;
            sell_house->belong = -1;
            sell_house->level = 0;

            //清除卖家的house_index对应的房子相对位置数组元素
            p->house_num--;
            for(j=i;j<p->house_num;j++){
                p->house_index[j]=p->house_index[j+1];
            }
            return true;
        }
    }
    return false;
}

/*
    by  郭一兴
    function：升级房子
*/
bool updateHouse(GAME* g)
{
    PLAYER *p = &(g->players[g->playerIndex]);
    LOCATION *loc = &(g->map.local[p->index]);
    if(loc->attr == 1){
        int cash = loc->cost * (loc->level+1);
        if(p->money < cash) {
            return false;
        }
        p->money -= cash;
        loc->level ++;
        return true;
    } else {
        return false;
    }
}

/*
    by  郭一兴
    function：支付租金
*/
bool payfees(GAME* g)
{
    PLAYER *player_pay = &(g->players[g->playerIndex]);
    LOCATION *loc = &(g->map.local[player_pay->index]);
    PLAYER *player_receive = NULL;
    int i;
    for(i=0;i<4;i++){
        if(loc->belong==g->players[i].id){
            player_receive = &(g->players[i]);
            break;
        }
    }
    if(loc->attr == 1){
        int cash = (loc->cost) * (loc->level+1) / 2;
        player_pay->money -= cash;
        player_receive->money += cash;
        if(player_pay->money <= 0){
            bankrupt(g);
            return false;
        }
        return true;
    } else {
        return false;
    }
}

/*
    by  郭一兴
    function：走到矿地，获得点数
*/
bool getPoints(GAME* g)
{
    PLAYER *p = &(g->players[g->playerIndex]);
    LOCATION *loc = &(g->map.local[p->index]);
    if(loc->attr == 7){
        int point = loc->cost;
        p->point+=point;
        return true;
    } else {
        return false;
    }
}

/*
    by 郭一兴
    function: 布置炸弹
*/
bool setBomb(GAME *g, int dist)
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
        return true;
    }
    else {
        return false;
    }
}

/*
    by 郭一兴
    function: 布置路障
*/
bool setBlock(GAME *g, int dist)
{
    PLAYER *p = &(g->players[g->playerIndex]);
    int locIndex = p->index + dist;
    if(locIndex<0){
        locIndex += MAP_SIZE;
    } else if(locIndex >= MAP_SIZE){
        locIndex -= MAP_SIZE;
    }
    LOCATION *loc = &(g->map.local[locIndex]);
    if(p->gift[1]>0 && loc->bomb==false && loc->block==false){
        loc->block = true;
        p->gift[1]--;
        return true;
    }
    else {
        return false;
    }
}

/*
    by 郭一兴
    function: 放置机器人
*/
bool setRobot(GAME *g)
{
    PLAYER *p = &(g->players[g->playerIndex]);
    if(p->gift[2]>0){
        int i;
        LOCATION *loc;
        for(i=1;i<=10;i++){
            loc = &(g->map.local[(p->index+i)%MAP_SIZE]);
            loc->block = loc->bomb = false;
        }
        p->gift[2]--;
        return true;
    } else {
        return false;
    }
}

void bankrupt(GAME *g){
    int i;
    PLAYER *p = &(g->players[g->playerIndex]);
    int money = p->money;
    // p->point = 0;
    // p->hospital_days = 0;
    // p->police_days = 0;

    // for(i=0;i<4;i++)
    //     p->gift[i]=0;
    while(p->house_num>0){
        sellHouse(g,p->house_index[p->house_num-1]);
    }
    p->money = money;
    p->status = 1;
    g->player_less_num --;
}

