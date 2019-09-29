#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "map.h"
#include "common.h"
#include <termios.h>
#include <errno.h>

char gamesymbols[] = {START, SPACE, HOSPITAL, PRISON, GIFTHOUSE, MAGIC, TOOLHOUSE, MINERAL};

// 初始化显示模块以及地图的数值
void initComponent(GAME*);
void initMap(GAME*);
// 绘制地图以及显示玩家模块（对外接口）
void drawMap(GAME*);
// 显示玩家
void drawPlayer(GAME*);
// 绘制玩家输入模块
void drawPlayerInput(GAME*);
void gotoXY(int, int);
void changeFontColor(char);
void changeBGColor(char);
// 清空背景
void clearBackground();
// 清空玩家输入模块
void clearInput(int);
// 清空消息提示模块
void clearMessage();
void hideMouse();
// 消息显示模块
void showMessage(char*);
// 显示系统提示
void showSystemMessage(char*);
// 清空系统提示
void clearSystemMessage();
// 显示查询
void showQuery(GAME*);
// 清除用户list
void clearQuery();
// 显示 round
void showRound(int);
// 游戏开启动画
void startAnimation();
// 游戏结束动画
void endAnimation();
// 清除道具
void clearBombOrBlock(GAME*);
// 显示游戏结束
void showGameOver();

int set_disp_mode(int fd,int option)  {
    /* by yss: FD=STDOUT_FILENO
                option=0可以禁止输入回显
                option=1可以打开回显示
                通过本函数和fflush的配合可以屏蔽键盘输入
                */
   int err;  
   struct termios term;  
   if(tcgetattr(fd,&term)==-1){  
     perror("Cannot get the attribution of the terminal");  
     return 1;  
   }  
   if(option)  
        term.c_lflag|=ECHOFLAGS;  
   else  
        term.c_lflag &=~ECHOFLAGS;  
   err=tcsetattr(fd,TCSAFLUSH,&term);  
   if(err==-1 && err==EINTR){  
        perror("Cannot set the attribution of the terminal");  
        return 1;  
   }  
   return 0;  
}  
void startAnimation() {
    set_disp_mode(STDOUT_FILENO, 0);
    int x, y, maxX;
    y = 0;
    x = HEIGHT - 16;
    while (x) {
        clearBackground();
        changeFontColor('B');
        gotoXY(x, 0);
        printf("        ██████╗ ██╗ ██████╗██╗  ██╗███╗   ███╗ █████╗ ███╗   ██╗      ██████╗ \n        ██╔══██╗██║██╔════╝██║  ██║████╗ ████║██╔══██╗████╗  ██║      ╚════██╗\n        ██████╔╝██║██║     ███████║██╔████╔██║███████║██╔██╗ ██║█████╗ █████╔╝\n        ██╔══██╗██║██║     ██╔══██║██║╚██╔╝██║██╔══██║██║╚██╗██║╚════╝██╔═══╝ \n        ██║  ██║██║╚██████╗██║  ██║██║ ╚═╝ ██║██║  ██║██║ ╚████║      ███████╗\n        ╚═╝  ╚═╝╚═╝ ╚═════╝╚═╝  ╚═╝╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝      ╚══════╝\n                                                                              ");
        printf("\n\n                                    _____       _             _ _       \n                                   |____ |     | |           | (_)      \n        __ _ _ __ ___  _   _ _ __      / /  ___| |_ _   _  __| |_  ___  \n       / _` | '__/ _ \\| | | | '_ \\     \\ \\ / __| __| | | |/ _` | |/ _ \\ \n      | (_| | | | (_) | |_| | |_) |.___/ / \\__ \\ |_| |_| | (_| | | (_) |\n       \\__, |_|  \\___/ \\__,_| .__/ \\____/  |___/\\__|\\__,_|\\__,_|_|\\___/ \n        __/ |               | |                                         \n       |___/                |_|                                         \n");
        usleep(200000);
        --x;
    }
    sleep(1);
    fflush(stdout);
    clearBackground();
    set_disp_mode(STDOUT_FILENO, 1);
}

void initComponent(GAME *g) {
    changeFontColor('X');
    gotoXY(MESSAGEX, MESSAGEY);
    printf(MESSAGE);
    gotoXY(SYSTEMMESSAGEX, SYSTEMMESSAGEY);
    printf(SYSTEMMESSAGE);
    gotoXY(ROUNDX, ROUNDY);
    changeFontColor(ROUNDCOLOR);
    printf(ROUND);
    showRound(g->rounds);
    drawMap(g);
    return;
}

void initMap(GAME *g) {
    
    clearBackground();
    hideMouse();
    FILE *fp;
    int index;
    index = 0;
    if ((fp = fopen("./document/map.txt", "r")) == NULL) {
        printf("文件错误\n");
        return;
    }
    while (index < 70) {
        fscanf(fp, "%d%d%d", &(g->map.local[index].x), &(g->map.local[index].y), &(g->map.local[index].attr));
        g->map.local[index].bomb = 0;
        g->map.local[index].block = 0;
        g->map.local[index].belong = -1;
        g->map.local[index].level = 0;
        if (g->map.local[index].attr == 1 || g->map.local[index].attr == 7) {
            fscanf(fp, "%d", &(g->map.local[index].cost));
        }
        ++index;
    }
    // startAnimation();
    initComponent(g);
    fclose(fp);
    return;
}

void clearBombOrBlock(GAME *g) {
    int mapIndex;
    mapIndex = g->players[g->playerIndex].index;
    if (g->map.local[mapIndex].x == 0) {
        gotoXY(g->map.local[mapIndex].x + 1, g->map.local[mapIndex].y);
    } else if (g->map.local[mapIndex].x == 7) {
        gotoXY(g->map.local[mapIndex].x - 1, g->map.local[mapIndex].y);
    } else if (g->map.local[mapIndex].y == 28) {
        gotoXY(g->map.local[mapIndex].x, g->map.local[mapIndex].y - 1);
    }
    printf(" ");
    return;
}

void drawMap(GAME *g) {
    
    int i, flag;
    changeFontColor('X');
    clearQuery();
    for (i = 0; i < 70; ++i) {
        flag = 0;
        gotoXY(g->map.local[i].x, g->map.local[i].y);
        if (1 == g->map.local[i].attr) {
            // 根据土地等级、归属绘制土地
            if (g->map.local[i].belong != -1) {
                changeFontColor(g->players[g->map.local[i].belong - 1].name);
                flag = 1;
            }
            printf("%d", g->map.local[i].level);
            changeFontColor('X');
        } else {
            // 绘制其他土地
            printf("%c", gamesymbols[g->map.local[i].attr]);
        }
        if (flag) {
            if (g->map.local[i].x == 0) {
                gotoXY(g->map.local[i].x + 1, g->map.local[i].y);
            } else if (g->map.local[i].x == 7) {
                gotoXY(g->map.local[i].x - 1, g->map.local[i].y);
            } else if (g->map.local[i].y == 28) {
                gotoXY(g->map.local[i].x, g->map.local[i].y - 1);
            }
        } else {
            gotoXY(g->map.local[i].x, g->map.local[i].y);
        }
        if (g->map.local[i].bomb) {
            // 绘制炸弹
            printf("@");
        } else if (g->map.local[i].block) {
            // 绘制路障
            printf("#");
        }
    }
    drawPlayer(g);
    return;
}

void drawPlayer(GAME *g) {
    
    int i, index;
    index = g->playerIndex;
    for (i = 0; i < g->player_num; ++i) {
        index = (index + 1) % g->player_num;
        if (g->players[index].status) {
            continue;
        }
        changeFontColor(g->players[index].name);
        gotoXY(g->map.local[g->players[index].index].x, g->map.local[g->players[index].index].y);
        printf("%c", g->players[index].name);
        changeFontColor('X');
    }
    clearInput(0);
    drawPlayerInput(g);
    fflush(stdout);
    return;
}

void gotoXY(int x, int y) {
    
    fflush(stdout);
    printf("%c[%d;%df", 0x1B, x + 1, y + 1);
    return;
}

void changeFontColor(char c) {
    
    char *color = NULL;

    color = (char*)calloc(8, sizeof(char));

    if (c == 'Q')
        // 设置红色前景 
        sprintf(color, "%d", 31);
    else if (c == 'A')
        // 设置绿色前景 
        sprintf(color, "%d", 32);
    else if (c == 'S')
        // 设置蓝色前景 
        sprintf(color, "%d", 34);
    else if (c == 'J')
        // 设置棕色前景 
        sprintf(color, "%d", 33);
    else if (c == 'W') 
        // 设置亮白色前景
        sprintf(color, "%d;%d", 1, 37);
    else if (c == 'E')
        // 游戏结束的走马灯字体
        sprintf(color, "%d;%d", 1, 30);
    else if (c == 'G')
        sprintf(color, "%d;%d", 1, 31);
    else
        // 设置黑色前景 
        sprintf(color, "%d", 30);
    printf("\033[%sm", color);
    free(color);
    return;
}

void changeBGColor(char c) {
    
    int color;
    switch (c) {
        case 'W':
            color = 47;
            break;
        case 'B':
            color = 40;
            break;
    }
    printf("\033[%dm", color);
    return;
}

void clearBackground() {
    
    int i, j;
    printf("\033[2J");
    changeBGColor('W');
    for (i = 0; i < HEIGHT; ++i) {
        for (j = 0; j < WIDTH; ++j) {
            printf(" ");
        }
        printf("\n");
    }
    gotoXY(0, 0);
    return;
}

void clearInput(int i) {
    
    if (IS_DEBUG) {
        i += IS_DEBUG_NAME_LENGTH;
    }
    gotoXY(INPUTX, i);
    for (; i < WIDTH; ++i) {
        printf(" ");
    }
    return;
}

void showRound(int rounds) {

    char *str = NULL;
    str = (char *)calloc(5, sizeof(char));

    sprintf(str, "%d", rounds);
    gotoXY(ROUNDX + 1, ROUNDY + ROUNDLENGTH / 2 - 2 + (strlen(str) + 1) / 2);
    changeFontColor(ROUNDCOLOR);
    printf("%s", str);
    changeFontColor('X');
    free(str);
    return;
}

void showMessage(char *message) {

    int y;
    clearSystemMessage();
    clearMessage();
    gotoXY(MESSAGEX + 1, 0);
    printf("%s", message);

    y = INPUTY + 8;
    changeFontColor('S');
    clearInput(y);
    if (IS_DEBUG) {
        y += IS_DEBUG_NAME_LENGTH;
    }
    gotoXY(INPUTX, y);
    return;
}

void showQuery(GAME *g) {
    
    int y, x;
    x = -1;
    changeFontColor('X');
    gotoXY(QMONEYX, QMONEYY);
    printf("%s%d", QMONEY, g->players[g->playerIndex].money);
    gotoXY(QPOINTX, QPOINTY);
    printf("%s%d", QPOINT, g->players[g->playerIndex].point);
//    gotoXY(QBOMBX, QBOMBY);
//    printf("%s%d", QBOMB, g->players[g->playerIndex].gift[0]);
    gotoXY(QBLOCKX + x, QBLOCKY);
    printf("%s%d", QBLOCK, g->players[g->playerIndex].gift[1]);
    gotoXY(QROBOTX + x, QROBOTY);
    printf("%s%d", QROBOT, g->players[g->playerIndex].gift[2]);
    gotoXY(QBLESSX + x, QBLESSY);
    printf("%s%d", QBLESS, g->players[g->playerIndex].bless_days);
    gotoXY(QINDEXX + x, QINDEXY);
    printf("%s%d", QINDEX, g->players[g->playerIndex].index);
    gotoXY(QHOUSEX + x, QHOUSEY);
    printf(QHOUSE);
    for (y = g->players[g->playerIndex].house_num; y > 0; --y) {
        printf("%d ", g->players[g->playerIndex].house_index[y - 1]);
    }

    clearSystemMessage();
    clearMessage();
    y = INPUTY + 8;
    clearInput(y);
    changeFontColor('S');
    if (IS_DEBUG) {
        y += IS_DEBUG_NAME_LENGTH;
    }
    gotoXY(INPUTX, y);

    return;
}

void clearQuery() {
    
    int i;
    gotoXY(QMONEYX, QMONEYY);
    for (i = QMONEYY; i < WIDTH; ++i) {
        printf(" ");
    }
    gotoXY(QPOINTX, QPOINTY);
    for (i = QPOINTY; i < WIDTH; ++i) {
        printf(" ");
    }
    gotoXY(QBOMBX, QBOMBY);
    for (i = QBOMBY; i < WIDTH; ++i) {
        printf(" ");
    }
    gotoXY(QBLOCKX, QBLOCKY);
    for (i = QBLOCKY; i < WIDTH; ++i) {
        printf(" ");
    }
    gotoXY(QROBOTX, QROBOTY);
    for (i = QROBOTY; i < WIDTH; ++i) {
        printf(" ");
    }
    gotoXY(QBLESSX, QBLESSY);
    for (i = QBLESSY; i < WIDTH; ++i) {
        printf(" ");
    }
    gotoXY(QINDEXX, QINDEXY);
    for (i = QINDEXY; i < WIDTH; ++i) {
        printf(" ");
    }
    gotoXY(QHOUSEX, QHOUSEY);
    for (i = QHOUSEY; i < WIDTH; ++i) {
        printf(" ");
    }
    return;
}

void clearMessage() {
    
    int i, j;
    for (i = MESSAGEX + 1; i < HEIGHT; ++i) {
        gotoXY(i, 0);
        for (j = 0; j < WIDTH; ++j) {
            printf(" ");
        }
    }
    return;
}

void showSystemMessage(char *systemMessage) {

    int y;

    clearMessage();
    clearSystemMessage();
    gotoXY(SYSTEMMESSAGEX, SYSTEMMESSAGEY + SYSTEMMESSAGELENGTH);
    printf("%s", systemMessage);
    y = INPUTY + 8;
    clearInput(y);
    changeFontColor('S');
    if (IS_DEBUG) {
        y += IS_DEBUG_NAME_LENGTH;
    }
    gotoXY(INPUTX, y);
    return;
}
void showHelp(){
    changeFontColor('X');
    char *str = "所有输入不区分大小写\nRoll\t掷骰子命令。行走1～6步，步数由随机算法产生\nSell n\t轮到玩家时，可出售自己的任意房产，出售价格为投资总成本的2\nBlock n\t玩家可将路障放置到离当前位置前后10步的任何位置，任一玩家经过路障，将被拦截。该道具一次有效\nRobot\t使用该道具，可清扫前方路面上10步内的任何其他道具，如炸弹、路障\nQuery\t显示自家资产\nHelp\t查看命令帮助\nQuit\t强制退出\n";
    showMessage(str);
    return;
}
void clearSystemMessage() {
    
    gotoXY(SYSTEMMESSAGEX, SYSTEMMESSAGEY + SYSTEMMESSAGELENGTH);
    int i;
    for (i = SYSTEMMESSAGEY + SYSTEMMESSAGELENGTH; i < WIDTH; ++i) {
        printf(" ");
    }
    return;
}

void drawPlayerInput(GAME *g) {

    gotoXY(INPUTX, INPUTY);
    changeFontColor('X');
    if (IS_DEBUG) {
        printf("管理员——");
    }
    changeFontColor(g->players[g->playerIndex].name);
    switch (g->players[g->playerIndex].name) {
        case 'Q':
            printf("钱夫人");
            break;
        case 'S':
            printf("孙小美");
            break;
        case 'A':
            printf("阿土伯");
            break;
        case 'J':
            printf("金贝贝");
            break;
        default:
            printf("X X X ");
    }
    changeFontColor('X');
    printf(INPUT);
    fflush(stdout);
    // 将用户输入的文字变蓝
    changeFontColor('S');
    return;
}

void hideMouse() {

    printf("\033[?25l");
    return;
}

void termctl(char *command){
    struct winsize w;
    printf("\e[8;%d;%dt\n", HEIGHT, WIDTH);
}

void endAnimation() {

    FILE *endText;
    int line, i;
    char *str[ENDANIMATIONHEIGHT];

    signal(SIGINT, NULL);
    line = 0;
    endText = fopen("./document/thank.txt", "r");

    set_disp_mode(STDOUT_FILENO, 0);

    while (line < ENDANIMATIONHEIGHT) {
        str[line] = (char*)calloc(100, sizeof(char));
        fgets(str[line], 100, endText);
        ++line;
    }

    line = 0;
    changeFontColor('E');
    while (line < ENDANIMATIONHEIGHT - HEIGHT) {
        clearBackground();
        for (i = 0; i < HEIGHT; ++i) {
            printf("%s", str[i + line]);
        }
        ++line;
        usleep(200000);
    }
    sleep(1);
    set_disp_mode(STDOUT_FILENO, 1);
    clearBackground();

    return;
}

void showGameOver() {
    if(!IS_DEBUG){
        int x, y;
        FILE *fp;
        char gameOver[1024];
        fp = fopen("document/gameOver.txt", "r");
        x = 2;
        y = 2;
        changeFontColor('G');

        while (x < 5) {
            gotoXY(x, y);
            fgets(gameOver, 1024, fp);
            printf("%s", gameOver);
            ++x;
        }
        fclose(fp);
        return;
    }
    return;
}
