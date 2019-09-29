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

    set_disp_mode(STDOUT_FILENO, 0);
    fflush(stdout);
    _Bool isBomb, isBlock;
    isBomb = 0;
    isBlock = 0;

    if (step > 6 || step < 0) {
        return;
    }
    if (!flag) {
        step = roll();
    }
    while (step) {
        step -= 1;
        g->players[g->playerIndex].index = (g->players[g->playerIndex].index + 1) % MAP_SIZE;
        //判断炸弹
        if (g->map.local[g->players[g->playerIndex].index].bomb){
            g->map.local[g->players[g->playerIndex].index].bomb = 0;
            clearBombOrBlock(g);
            getin_hospital(g);
            isBomb = 1;
        } else if (g->map.local[g->players[g->playerIndex].index].block){
            g->map.local[g->players[g->playerIndex].index].block = 0;
            clearBombOrBlock(g);
            isBlock = 1;
        }
        usleep(250000);
        drawMap(g);
        if (isBomb || isBlock) {
            break;
        }
    }
    if (!isBomb) {
        //到达目的地，进行判断
        int state = g->map.local[g->players[g->playerIndex].index].attr;
        switch (state) {
            case 1: //House
                getin_house(g);
                break;
            case 3: //POLICE
                // getin_police(g); version2.0 delete polistation
                break;
            case 4: //GIFT
                getin_gifthouse(g);
                break;
            case 5: //MAGICHOUSE
                getin_magic_house(g);
                break;
            case 6: //TOOLHOUSE
                getin_toolhouse(g);
                break;
            case 7: //Mininal
            {
                int cost = g->map.local[g->players[g->playerIndex].index].cost;
                g->players[g->playerIndex].point += cost;
                sprintf(str,"%s在矿地获得%d点数\n", getName(g->players[g->playerIndex].name), cost);
                showMessage(str);
                sleep(1);
                break;
            }
            default:
                break;
        }
    }
    nextIndex(g);
    gameOver(g);
}
