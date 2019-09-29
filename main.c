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
    RESET = 0;
    IS_DEBUG = 1;
    START = 1;
/*    if(argc==1){
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
    }*/  
    termctl(NULL);
    GAME g;
    signal(SIGINT, pleaseQuit);
    startAnimation();
    char command[100];
    g.player_num = 0;
    g.playerIndex = 0;
    g.rounds = 1;
    clearBackground();
    //if(!IS_DEBUG){
        int load = 0;
        _Bool fileFlag = 0;
        FILE *fp = fopen(".arch", "rb");
        // 存档读取
            if (fp != NULL) {
                fileFlag = 1;
                printf("发现游戏存档，请问是否读取存档内容[Y/N/Reset]\n");
            } else {
                printf("输入回车进入游戏\n");
            }
            char load_input[20];
            while (1) {
                memset(load_input, 20, '\0');
                fgets(load_input, 20, stdin);
                Command *cmd = CommandParser(load_input);
                if (cmd != NULL && cmd->params[0] == COMMAND_RESET_INDEX) {
                    command_exec(cmd, &g);
                    break;
                }
                if (!fileFlag) {
                    break;
                }
                if (fileFlag && (load_input[0]=='Y' || load_input[0]=='y' || load_input[0]=='\n')) {
                    load = 1;
                    break;
                }
                if (fileFlag && (load_input[0]=='N' || load_input[0]=='n')) {
                    load = 0;
                    break;
                }
                printf("wrong input.");
            }
            if (fileFlag) {
                fclose(fp);
            }
        if (!RESET) {
            clearBackground();
            if (!load) {
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
            } else {
                fp = fopen(".arch", "rb");
                fread(&g, sizeof(GAME), 1, fp);
                fclose(fp);
                g.save_path = "result.txt";
                initComponent(&g);
                drawMap(&g);
            }
        }
    //}
    START = 0;
    while (1) {
        set_disp_mode(STDOUT_FILENO, 1);
        fflush(stdout);
        fgets(command, 100, stdin);
        set_disp_mode(STDOUT_FILENO, 0);
        fflush(stdout);
        if(command_exec(CommandParser(command), &g)){
        }
    }
    return 0;
}
