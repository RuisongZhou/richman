//
// Created by 周瑞松 on 2019/9/14.
//

#include "building.h"
#include "judge.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char str[BUF_SIZE];

void Input(char* s)
{
    set_disp_mode(STDOUT_FILENO, 1);
    fflush(stdout);
    fgets(s, 10, stdin);
    set_disp_mode(STDOUT_FILENO, 0);
    fflush(stdout);
}

int judgeMoney(int money)
{
    char inputMoney[10];
    while (money <1000 || money > 50000){
        if (money == 0)
            return 10000;
        printf("输入错误！设置玩家初始资金，范围1000～50000（默认10000）");
        Input(inputMoney);
        //fgets(inputMoney, 10 ,stdin);
        money = 0;
        if (inputMoney[0] != '\n'){
            money = atoi(inputMoney);
        }
    }
    return money;
}

char* judgePlayer(char* inputPlayers)
{

    int wrong = 1;
    char *returnPlayers;
    while (wrong){
        wrong = 0;
        int length = strlen(inputPlayers) -1;
        inputPlayers[length] = '\0';
        int a[5] = {0};
        //printf("%d\n", length);
        if ( length < 2 || length > 4){
            printf("错误输入！请选择2～4位不重复玩家，输入编号即可（1、钱夫人；2、阿土伯；3、孙小美；4、金贝贝）");
            wrong = 1;
            //fgets(inputPlayers, 10, stdin);
            Input(inputPlayers);
            continue;
        }
        returnPlayers = (char*)malloc((length+1)* sizeof(char));
        returnPlayers[0] = '0'+length;
        for(int i = 0; i < length; i++){
            int numplayers = inputPlayers[i] - '0';
            //ensure the difference of the players
            a[numplayers] +=1;
            //printf("%d\n", numplayers);
            if (numplayers < 1 || numplayers > 4 || a[numplayers] > 1 ){
                printf("错误输入！请选择2～4位不重复玩家，输入编号即可（1、钱夫人；2、阿土伯；3、孙小美；4、金贝贝）");
                wrong = 1;
                //fgets(inputPlayers,10,stdin);
                Input(inputPlayers);
                continue;
            } else {
                returnPlayers[i+1] = '0' + numplayers;
            }
        }
    }
    return returnPlayers;
}

char judgeYN(char *s) {
    char ry = 'Y';
    char rn = 'N';
    while (('y' != *s) && ('Y' != *s) && ('n' != *s) && ('N' != *s)) {
        sprintf(str, "错误输入！购买请按Y（y），不购买请按N（n）");
        showMessage(str);
        *s = getInput();
    }
    if ('y' == *s || 'Y' == *s) {
        return ry;
    } else {
        return rn;
    }
}

void addRounds(GAME *g) {

    if(g->players[g->playerIndex].bless_days){
        g->players[g->playerIndex].bless_days -=1;
    }

    g->playerIndex = (g->playerIndex + 1) % g->player_num;
    if (!g->playerIndex) {
        g->rounds += 1;
        showRound(g->rounds);
    }
    return;
}

void changePlayerStatus(GAME *g) {
    
    if (!(g->players[g->playerIndex].playerStatus)) {
        char *message = NULL;
        message = (char*)calloc(50, sizeof(char));
        
        if (g->players[g->playerIndex].hospital_days) {
            g->players[g->playerIndex].hospital_days -= 1;
            sprintf(message, "%s住院一天，剩余住院%d天", getName(g->players[g->playerIndex].name), g->players[g->playerIndex].hospital_days);
        }
        
        if (g->players[g->playerIndex].police_days) {
            g->players[g->playerIndex].police_days -= 1;
            sprintf(message, "%s拘留一天，剩余拘留%d天", getName(g->players[g->playerIndex].name), g->players[g->playerIndex].police_days);
        }

        if (g->players[g->playerIndex].magic_time){
            if (g->map.local[g->players[g->playerIndex].index].attr == 1){
                getin_house(g);
            } else if (g->map.local[g->players[g->playerIndex].index].attr == 7){
                int cost = g->map.local[g->players[g->playerIndex].index].cost;
                g->players[g->playerIndex].point += cost;
                sprintf(str, "%s在矿地获得%d点数\n", getName(g->players[g->playerIndex].name), cost);
                showMessage(str);
            }
            if (!(g->players[g->playerIndex].playerStatus)) {
                sleep(1);
                g->players[g->playerIndex].magic_time -= 1;
                sprintf(message, "%s被诅咒!剩余%d回合\n", getName(g->players[g->playerIndex].name), g->players[g->playerIndex].magic_time);
            }
        }
        showMessage(message);
        free(message);
        sleep(1);
        drawMap(g);
    }    
            
    addRounds(g);
    return;
}

// 切换玩家
void nextIndex(GAME* g) {
    
    addRounds(g);
    drawMap(g);
    
    while (g->players[g->playerIndex].police_days || g->players[g->playerIndex].hospital_days || g->players[g->playerIndex].playerStatus ||
    g->players[g->playerIndex].magic_time) {
        changePlayerStatus(g);
    }
    
    return;
}
