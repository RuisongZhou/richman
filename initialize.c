//
// Created by 周瑞松 on 2019/9/14.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "initialize.h"
#include "judge.h"
#include "map.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void pleaseQuit(int s) {
    char *systemMessage = NULL;
    systemMessage = (char *)calloc(20, sizeof(char));
    systemMessage = "请输入命令Quit退出游戏";
    showSystemMessage(systemMessage);
    fflush(stdout);
}

void playMusic() {
    //system("nohup mplayer -playlist ./music/music.lst -loop 0");
    system("./auplay/test");
}

void initialize(GAME *game_pointer, int money, char* c)
{
    char *P;
    if (!IS_DEBUG){
//        pthread_create(&(game_pointer->music), NULL, (void *)&playMusic, NULL);
 //       pthread_detach(game_pointer->music);
    }
    P = judgePlayer(c);
    printf("%s",P);
    int num = P[0]-'0';
    game_pointer->player_num = num;
    game_pointer->player_less_num = num;
    for ( int i = 0; i < 4; i++){
        game_pointer->players[i].status = 1;
    }
    for ( int i = 1; i <= num; i++){
        init_player(&(game_pointer->players[i-1]), i, money, P[i]);
    }
    game_pointer->save_path =  (char*)"./result.txt";
    game_pointer->playerIndex = 0;
    free(P);
}


void init_player(PLAYER *player, int id, int money, char symbol)
{
    player->id = id;
    player->index = 0;
    switch (symbol-'0')
    {
        case 1:
            //strcpy(player->name ,P_QFR);
            player->name = P_QFR;
            break;
        case 2:
            //strcpy(player->name ,P_ASB);
            player->name = P_ATB;
            break;
        case 3:
            //strcpy(player->name ,P_SXM);
            player->name = P_SXM;
            break;
        case 4:
            //strcpy(player->name ,P_JBB);
            player->name = P_JBB;
            break;
    };
    player->money = money;
    player->point = 200;
    player->house_num = 0;
    player->hospital_days = 0;
    player->police_days = 0;
    player->magic_time = 0;
    player->bless_days = 0;
    player->magic_time = 0;
    player->status = 0;
    player->index = 0;
    for (int i = 0; i < 3; i++)
    {
        player->gift[i] = 0;
    }
    for (int i = 0; i < MAP_SIZE; i++){
        player->house_index[i] = 0;
    }
}

void init_reset(GAME* g, char* P)
{
    g->playerIndex = 0;
    int num = P[0]-'0';
    g->player_num = num;
    g->player_less_num = num;
    for ( int i = 0; i < 4; i++){
        g->players[i].status = 1;
    }
    for ( int i = 1; i <= num; i++){
        init_player(&(g->players[i-1]), i, 10000, P[i]);
        g->players[i-1].point = 200;
    }
    g->rounds = 1;
    g->save_path = "./result.txt";
    g->playerIndex = 0;
}

void quit() {
    if(IS_DEBUG)
        return;
    set_disp_mode(STDOUT_FILENO, 0);
    int waitTime = 3;
    char *systemMessage = NULL;
    systemMessage = (char *)calloc(30, sizeof(char));
    while (waitTime) {
        sprintf(systemMessage, "\033[1;34m游戏即将在\033[1;31m%d\033[1;34m秒后退出", waitTime);
        showSystemMessage(systemMessage);
        sleep(1);
        --waitTime;
    }
    endAnimation();
    set_disp_mode(STDOUT_FILENO, 1);
    printf("\033[0m");
    printf("\033[?25h");
    printf("\033[2J");
    fflush(stdout);
}

void changeStatusWithSetRounds(GAME *g, int rounds) {

    int i, playerIndex;
    while (rounds) {
        playerIndex = g->playerIndex;
        for (i = 0; i < g->player_num; ++i) {
            if (!g->players[playerIndex].status) {
                changePlayerStatus(g);
            }
            playerIndex = (playerIndex + 1) % g->player_num;
        }
        --rounds;
    }
    return;
}
