#include "playerMove.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "judge.h"

static char str[BUF_SIZE];

void playerMove(GAME*, int, int);
int roll();

int roll() {
    srand(time(NULL));
    return rand() % 6 + 1;
}

void playerMove(GAME *g, int step, int flag) {

    if (step > 6 || step < 0) {
        return;
    }
    if (!flag) {
        step = roll();
    }
    while (step) {
        step -= 1;
        ++g->players[g->playerIndex].index;
        //判断炸弹
        if(g->map.local[g->players[g->playerIndex].index].bomb){
            getin_hospital(g);
            g->map.local[g->players[g->playerIndex].index].bomb = false;
            return;
        } else if (g->map.local[g->players[g->playerIndex].index].block){
            break;
        }
        drawMap(g);
        sleep(1);
    }
    //到达目的地，进行判断
    int state = g->map.local[g->players[g->playerIndex].index].attr;
    switch (state) {
        case 1: //House
            getin_house(g);
            break;
        case 3: //POLICE
            getin_police(g);
            break;
        case 4: //GIFT
            getin_gifthouse(g);
            break;
        case 5: //MAGICHOUSE
            break;
        case 6: //TOOLHOUSE
            getin_toolhouse(g);
            break;
        case 7: //Mininal
        {
            int cost = g->map.local[g->players[g->playerIndex].index].cost;
            g->players[g->playerIndex].point += cost;
            sprintf(str,"玩家%c在矿地获得%d点数\n", g->players[g->playerIndex].name, cost);
            showMessage(str);
            break;
        }
        default:
            break;
    }
    nextIndex(g);
}
