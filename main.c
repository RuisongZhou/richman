//#include <stdio.h>
//
//#include <stdio.h>
//#include <stdlib.h>
#include "initialize.h"
#include "command_parser.h"
#include "command_exec.h"
#include "map.h"
#include "judge.h"
#include "unistd.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char **argv) {
    if(argc==1){
        IS_DEBUG = 0;
    }
    else{
        if(argc!=2){
            printf("rich.exe $IS_DEBUG\n");
            exit(0);
        }
        if(strlen(argv[1])!=1){
            printf("rich.exe 0 || rich.exe 1");
            exit(0);
        }
        if(argv[1][0] == '1'){
            IS_DEBUG = 1;
        }
        else{
            if(argv[1][0] == '0'){
                IS_DEBUG = 0;
            }
            else{
                printf("rich.exe $IS_DEBUG\n");
                exit(0);
            }
        }
    }
    termctl(NULL);
    GAME g;
    if(!IS_DEBUG){
        signal(SIGINT, pleaseQuit);
        startAnimation();
    }
    char command[100];
    g.player_num = 0;
    g.playerIndex = 0;
    g.rounds = 1;
    if(!IS_DEBUG){
        int load = 0;
        FILE *fp = fopen(".arch", "rb");
        if(fp!=NULL){
            // initMap(&g);
            printf("game archieve detected. Load archieve or not? [Y/n]");
            char load_input[1024];
            while(1){
                memset(load_input, 1024, '\0');
                fgets(load_input, 1024, stdin);
                if(strlen(load_input)>2){
                    printf("wrong input.");
                    continue;
                }
                if(load_input[0]=='Y' || load_input[0]=='y' || load_input[0]=='\n'){
                    load = 1;
                    break;
                }
                if(load_input[0]=='N' || load_input[0]=='n'){
                    load = 0;
                    break;
                }
                printf("wrong input.");
                continue;
            }
        }
        if(!load){
            char inputMoney[10];
            char c[10];
            int money = 10000;
            printf("设置玩家初始资金，范围1000～50000（默认10000）");
            fgets(inputMoney,10,stdin);
            if (inputMoney[0] != '\n'){
                money = atoi(inputMoney);
            }
            money = judgeMoney(money);
            printf("请选择2～4位不重复玩家，输入编号即可（1、钱夫人；2、阿土伯；3、孙小美；4、金贝贝）");
            fgets(c,10,stdin);
            initialize(&g, money, c);
            initMap(&g);
        }
        else{
            fread(&g, sizeof(GAME), 1, fp);
            g.save_path = "result.txt";
            initComponent(&g);
            drawMap(&g);
        }
    }
    while (1) {
        if(!IS_DEBUG)
        {
            set_disp_mode(STDOUT_FILENO, 1);
            fflush(stdout);
        }
        fgets(command, 100, stdin);
        if(!IS_DEBUG)
        {
            set_disp_mode(STDOUT_FILENO, 0);
            fflush(stdout);
        }
        if(command_exec(CommandParser(command), &g)){
            // drawMap(&g);
        }
    }
    return 0;
}
