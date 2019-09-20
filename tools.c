#include "tools.h"

void set_block(int n,int index,GAME*g){
    int label;
    label = g->players[g->playerIndex].index;
    g->map.local[(label+n)%70].block = 1;
}

void set_bomb(int n,int index,GAME*g){
    int label;
    label = g->players[g->playerIndex].index;
    g->map.local[(label+n)%70].bomb = 1;
}

void set_robot(int index,GAME*g){
    int i, label;
    label = g->players[g->playerIndex].index;
    for(i=label-10;i<label+10;++i){
        if (g->map.local[(i)%70].bomb||g->map.local[(i)%70].block){
            g->map.local[(i)%70].bomb = 0;
            g->map.local[(i)%70].block = 0;
        }
    }
}
