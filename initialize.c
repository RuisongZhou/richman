//
// Created by 周瑞松 on 2019/9/14.
//

#include <stdio.h>
#include <string.h>
#include "initialize.h"
#include "judge.h"

void initialize(GAME *game_pointer,int money, char* c)
{
    char *P;
    P = judgePlayer(c);
    printf("%s",P);
    int num = P[0]-'0';
    game_pointer->player_num = num;
    for ( int i = 1; i <= num; i++){
        init_player(&(game_pointer->players[i-1]),P[i]-'0',money);
    }
    game_pointer->rounds = 0;
    game_pointer->save_path =  (char*)"./result.txt";
    game_pointer->playerIndex = 0;
    free(P);
}


void init_player(PLAYER *player, int id, int money)
{
    player->id = id;
    player->index = 0;
    switch (id)
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
    player->bless_days = 0;
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
    g->player_num = 0;
    int num = P[0]-'0';
    g->player_num = num;
    for ( int i = 1; i <= num; i++){
        init_player(&(g->players[i-1]),P[i]-'0',0);
        g->players[i-1].point = 0;
    }
    g->rounds = 0;
    g->save_path = NULL;
    g->playerIndex = 0;
}