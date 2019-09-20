//#include <stdio.h>
//
//#include <stdio.h>
//#include <stdlib.h>
#include "initialize.h"
#include "command_parser.h"
#include "command_exec.h"
#include "map.h"
#include "judge.h"

int main(int argc, char **argv) {
    termctl(argv[0]);
    startAnimation();
    GAME g;
    char command[100];
    g.player_num = 0;
    g.playerIndex = 0;
    signal(SIGINT, pleaseQuit);
    if(!IS_DEBUG){
        char inputMoney[10];
        char c[10];
        int money = 10000;
        printf("设置玩家初始资金，范围1000～50000（默认10000）");
        if (*gets(inputMoney) != '\n'){
            money = atoi(inputMoney);
        }
        money = judgeMoney(money);
        printf("请选择2～4位不重复玩家，输入编号即可（1、钱夫人；2、阿土伯；3、孙小美；4、金贝贝）");
        gets(c);
        initialize(&g, money, c);
        initMap(&g);
    }
    while (1) {
        fgets(command, 100, stdin);
        if(command_exec(CommandParser(command), &g)){
            // drawMap(&g);
        }
    }
    return 0;
}
