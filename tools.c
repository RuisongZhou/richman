#include "tools.h"

static char str[256];

void set_block(int n, GAME *g){
    if (g->players[g->playerIndex].gift[1]>0) {
        int label;
        label = (g->players[g->playerIndex].index + n + MAP_SIZE) % MAP_SIZE;
        if (g->map.local[label].block==1) {
            sprintf(str,"路障放置失败：地图 %d 号点已有路障", label);
        } else {
            sprintf(str,"路障放置成功，放置位置：地图 %d 号点", label);
            g->map.local[label].block = 1;
        }
        g->players[g->playerIndex].gift[1] -= 1;
    } else {
        sprintf(str, "你未持有路障，请勿无中生有");
    }
    showMessage(str);
    sleep(1);
    drawMap(g);
    return;
}

void set_bomb(int n, GAME *g){
    if (g->players[g->playerIndex].gift[0]>0) {
        int label;
        label = (g->players[g->playerIndex].index + n + MAP_SIZE) % MAP_SIZE;
        if (g->map.local[label].bomb==1) {
            sprintf(str,"炸弹放置失败：地图 %d 号点已有炸弹",label);
            showMessage(str);
        } else {
            sprintf(str,"炸弹放置成功，放置位置：地图 %d 号点。请牢记：恶人有恶报",label);
            showMessage(str);
            g->map.local[label].bomb = 1;
            drawMap(g);
        }
        g->players[g->playerIndex].gift[0] -= 1;
    } else {
        showMessage("你未持有炸弹，请勿无中生有");
    }
    return;
}

void set_robot(GAME *g){
    int i;
    if (g->players[g->playerIndex].gift[2]>0) {
        for(i = 0; i <= 10; ++i) {
            g->map.local[(i + g->players[g->playerIndex].index) % MAP_SIZE].bomb = 0;
            g->map.local[(i + g->players[g->playerIndex].index) % MAP_SIZE].block = 0;
        }
        showMessage("机器娃娃以帮你清除了路上的障碍物啦，乌拉～");
        drawMap(g);
        g->players[g->playerIndex].gift[2] -= 1;
    } else {
        showMessage("你未持有机器娃娃，请勿无中生有");
    }
    return;
}
