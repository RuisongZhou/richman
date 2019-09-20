//
// Created by 周瑞松 on 2019/9/14.
//

#include "judge.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char str[BUF_SIZE];

int judgeMoney(int money)
{
    char inputMoney[10];
    while (money <1000 || money > 50000){
        if (money == 0)
            return 10000;
        printf("输入错误！设置玩家初始资金，范围1000～50000（默认10000）");

        gets(inputMoney);
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
        int length = strlen(inputPlayers);
        int a[5] = {0};
        //printf("%d\n", length);
        if ( length < 2 || length > 4){
            printf("错误输入！请选择2～4位不重复玩家，输入编号即可（1、钱夫人；2、阿土伯；3、孙小美；4、金贝贝）");
            wrong = 1;
            gets(inputPlayers);
            continue;
        }
        returnPlayers = (char*)malloc((length+1)* sizeof(char));
        returnPlayers[0] = '0'+length;
        for(int i = 0; i < length; i++){
            int numplayers = inputPlayers[i] - '0';
            a[numplayers] +=1;
            //printf("%d\n", numplayers);
            if (numplayers < 1 || numplayers > 4 || a[numplayers] >1 ){
                printf("错误输入！请选择2～4位不重复玩家，输入编号即可（1、钱夫人；2、阿土伯；3、孙小美；4、金贝贝）");
                wrong = 1;
                gets(inputPlayers);
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
    
    g->playerIndex = (g->playerIndex + 1) % g->player_num;
    if (!g->playerIndex) {
        g->rounds += 1;
        showRound(g->rounds);
    }
    return;
}

void changePlayerStatus(GAME *g) {
    
    char *name = NULL;
    name = (char*)calloc(9, sizeof(char));
    char *message = NULL;
    message = (char*)calloc(50, sizeof(char));
    
    switch (g->players[g->playerIndex].name) {
        case 'Q':
            sprintf(name, "%s", "钱夫人");
            break;
        case 'S':
            sprintf(name, "%s", "孙小美");
            break;
        case 'J':
            sprintf(name, "%s", "金贝贝");
            break;
        case 'A':
            sprintf(name, "%s", "阿土伯");
            break;
    }
        
    if (g->players[g->playerIndex].hospital_days) {
        g->players[g->playerIndex].hospital_days -= 1;
        sprintf(message, "%s住院一天，剩余住院%d天", name, g->players[g->playerIndex].hospital_days);
    }
        
    if (g->players[g->playerIndex].police_days) {
        g->players[g->playerIndex].police_days -= 1;
        sprintf(message, "%s拘留一天，剩余拘留%d天", name, g->players[g->playerIndex].police_days);
    }
    
    if (!g->players[g->playerIndex].status) {
        showMessage(message);
    }
        
    if(g->players[g->playerIndex].bless_days){
        g->players[g->playerIndex].bless_days -=1;
    }
        
    addRounds(g);
    usleep(500000);
    showMessage(" ");
    free(name);
    free(message);
    return;
}

// 切换玩家
void nextIndex(GAME* g) {
    
    addRounds(g);
    
    while (g->players[g->playerIndex].police_days || g->players[g->playerIndex].hospital_days || g->players[g->playerIndex].status) {
        changePlayerStatus(g);
    }
    
    drawMap(g);
    return;
}
