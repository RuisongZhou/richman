#include "judge.h"
#include "building.h"
#include "action.h"
#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static char str[BUF_SIZE];
char getInput();
char *getName(char);

void getin_hospital(GAME* g){
    g->players[g->playerIndex].hospital_days = SLEEP_TIME_HOSPITAL;
    g->players[g->playerIndex].index = HOSPITAL_POS;
    sprintf(str, "你触发了炸弹进入医院，住院 %d 天", SLEEP_TIME_HOSPITAL);
    showMessage(str);
}

void getin_police(GAME* g){
    g->players[g->playerIndex].police_days = SLEEP_TIME_PRISON;
    printf("你被捕，入狱 %d 天", SLEEP_TIME_PRISON);
}

void getin_gifthouse(GAME* g){
    char n;
    sprintf(str,"欢迎来到礼品屋!\n输入1来获得2000元钱\n输入2来获得200点数\n输入3来获得财神的祝福\n按其他键退出");
    showMessage(str);
    n = getInput();
    switch (n)
    {
    case '1':
        g->players[g->playerIndex].money+=2000;
        sprintf(str,"金钱增加2000");
        showMessage(str);
        break;
    case '2':
        g->players[g->playerIndex].point+=200;
        sprintf(str,"点数增加200");
        showMessage(str);
        break;
    case '3':
        g->players[g->playerIndex].bless_days=5;
        sprintf(str,"财神附身，可免过路费5天");
        showMessage(str);
        break;
    default:
        sprintf(str," ");
        showMessage(str);
        break;
    }
}

char getInput() {
    char c;
    if(!IS_DEBUG){
        set_disp_mode(STDOUT_FILENO, 1);
        fflush(stdout);
    }
    fgets(str, BUF_SIZE, stdin);
    if(!IS_DEBUG){
        set_disp_mode(STDOUT_FILENO, 0);
        fflush(stdout);
    }
    if (strlen(str) != 2) {
        // 将输入设置成一个错误输入
        c = 'x';
    } else {
        c = str[0];
    }
    return c;
}

void getin_toolhouse(GAME* g){
    int n1,n2,n3,num,price, sum, flag;
    char action;
    int leftpoint;
    flag = 0;
    do
    {
    CIR:
        showMessage("欢迎来到工具屋!\n输入2购买路障(50点)\n输入3购买机器人(30点)\n输入f来离开工具屋");
        action = getInput();
        leftpoint = g->players[g->playerIndex].point;
        switch (action)
        {
        case '1':
//            if(leftpoint < 50){
//                sprintf(str, "余额不足，不能购买");
//                showMessage(str);
//                break;
//            }
//            g->players[g->playerIndex].point -= 50;
//            g->players[g->playerIndex].gift[0] += 1;
//            sprintf(str, "%s玩家，你买了一个炸弹，现在你有%d个炸弹,剩余点数：%d", getName(g->players[g->playerIndex].name),g->players[g->playerIndex].gift[0],g->players[g->playerIndex].point);
//            showMessage(str);
            break;
        case '2':
            if(leftpoint < 50){
                sprintf(str, "余额不足，不能购买");
                showMessage(str);
                break;
            }
            g->players[g->playerIndex].point -= 50;
            g->players[g->playerIndex].gift[1] += 1;
            sprintf(str, "%s玩家，你买了一个路障，现在你有%d个路障,剩余点数：%d", getName(g->players[g->playerIndex].name), g->players[g->playerIndex].gift[1],g->players[g->playerIndex].point);
            showMessage(str);
            break;
        case '3':
            if(leftpoint < 30){
                sprintf(str, "余额不足，不能购买");
                showMessage(str);
                break;
            }
            g->players[g->playerIndex].point -= 30;
            g->players[g->playerIndex].gift[2] += 1;
            sprintf(str, "%s玩家，你买了一个机器人，现在你有%d个机器娃娃,剩余点数：%d", getName(g->players[g->playerIndex].name), g->players[g->playerIndex].gift[2],g->players[g->playerIndex].point);
            showMessage(str);
            break;
        case 'f'://f的ascii值
        case 'F':
            flag = 1;
            break;
        default:
            showSystemMessage("输入有误，请按要求重新输入");
            goto CIR;
        }
        sleep(1);
        sum = g->players[g->playerIndex].gift[0] + g->players[g->playerIndex].gift[1] + g->players[g->playerIndex].gift[2];
    } while (g->players[g->playerIndex].point > 0 && sum < 10 && !flag);
    sprintf(str, "%s玩家，你现在拥有 %d 炸弹\n你现在拥有 %d 路障\n你现在拥有 %d 机器娃娃",getName(g->players[g->playerIndex].name), g->players[g->playerIndex].gift[0], g->players[g->playerIndex].gift[1], g->players[g->playerIndex].gift[2]);
    showMessage(str);
    if(!IS_DEBUG)
        sleep(2);
}

char *getName(char name) {
    switch (name) {
        case 'Q':
            return "\033[31m钱夫人\033[30m";
        case 'J':
            return "\033[33m金贝贝\033[30m";
        case 'S':
            return "\033[34m孙小美\033[30m";
        case 'A':
            return "\033[32m阿土伯\033[30m";
    }
    return "";
}

void getin_house(GAME *g)
{
    int owner = g->map.local[g->players[g->playerIndex].index].belong;
    int money = g->players[g->playerIndex].money;
    int price = g->map.local[g->players[g->playerIndex].index].cost;
    bool state;
    if(owner == -1){    //无人土地
        fflush(stdin);
        sprintf(str, "此块土地无人拥有，请问是否购买？土地价格：%d\n你拥有的金钱为:%d\n购买请按Y，不购买请按N", price, money);
        showMessage(str);
        char operation;
        operation = getInput();
        char res = judgeYN(&operation);
        if (res == 'Y'){
            state = buyHouse(g);
            if (state){
                sprintf(str, "购买成功，第%d号土地归%d号玩家%c所有.", g->players[g->playerIndex].index, g->players[g->playerIndex].id ,g->players[g->playerIndex].name);

            } else {
                sprintf(str,"购买失败!");
            }
            showMessage(str);
        } else {
            sprintf(str, "未进行购买");
            showMessage(str);
        }
        return;
    } else if (owner == g->players[g->playerIndex].id){   //自己的房子
        int level = g->map.local[g->players[g->playerIndex].index].level;
        if(level == 3){
            sprintf(str,"此块土地是你的，目前等级为满级");
            showMessage(str);
        } else {
            sprintf(str, "此块土地是你的，请问是否升级？升级价格：%d\n你拥有的金钱为:%d\n购买请按Y，不购买请按N", price, money );
            showMessage(str);
            char operation;
            operation = getInput();
            char res = judgeYN(&operation);
            if (res == 'Y'){
                state = updateHouse(g);
                if (state){
                    sprintf(str,"升级成功!");
                } else {
                    sprintf(str,"升级失败!");
                }
                showMessage(str);
            }
        }
        return;
    } else if (g->players[g->playerIndex].bless_days > 0) {
        //不需交钱
        sprintf(str,"财神附体，无需交钱。\n财神附体剩余轮数: %d", g->players[g->playerIndex].bless_days);
        showMessage(str);
    } else if (g->players[g->map.local[g->players[g->playerIndex].index].belong - 1].hospital_days) {
        // 地主住院不需要交租金
        char *name = getName(g->players[g->map.local[g->players[g->playerIndex].index].belong - 1].name);
        sprintf(str, "%s正在住院，你可以不用付租金啦～\n你可也得注意身体哟", name);
        showMessage(str);
    } else if (g->players[g->map.local[g->players[g->playerIndex].index].belong - 1].police_days) {
        // 地主被监禁不需要交租金
        char *name = getName(g->players[g->map.local[g->players[g->playerIndex].index].belong - 1].name);
        sprintf(str, "%s被监禁了，你可以不用付租金啦～\n小心驶得万年船", name);
        showMessage(str);
    } else {    //交钱
        state = payfees(g);
        int cost = price*( g->map.local[g->players[g->playerIndex].index].level +1);
        money = g->players[g->playerIndex].money;
        if(state){
            sprintf(str,"此块地玩家归%d号玩家所有，扣费%d元，剩余%d元", owner, cost/2, money);
        } else {
            sprintf(str,"你以破产!退出游戏.");
            bankrupt(g);
        }
        showMessage(str);
        sleep(1);
    }
}

void getin_magic_house(GAME *g)
{
    char n;
    char name[5][10];
    for (int i =0; i < 4; i++){
        char c = g->players[i].name;
        switch (c)
        {
            case 'Q':
                strcpy(name[i],"钱夫人");
                break;
            case 'A':
                strcpy(name[i],"阿土伯");
                break;
            case 'S':
                strcpy(name[i],"孙小美");
                break;
            case 'J':
                strcpy(name[i],"金贝贝");
                break;
        }
    }
    sprintf(str,"欢迎来到魔法屋!\n输入1来陷害1号玩家\n输入2来陷害2号玩家\n输入3来陷害3号玩家\n输入4来陷害4号玩家\n按0退出\n");
    showMessage(str);
    int flag = 1;
    do{
        n = getInput();
        int p = n- '0';
        if (p >=1 && p <=4){
            if (g->players[p-1].status){
                sprintf(str, "%d号玩家%s不存在！请重新输入。\n",p, name[p-1]);
                showMessage(str);
            }
            else if (g->players[p-1].magic_time){
                sprintf(str, "%d号玩家%s已经被诅咒！请重新输入。\n",p, name[p-1]);
                showMessage(str);
            } else {
                flag = 0;
                g->players[p-1].magic_time = MAGIC_TIME;
                sprintf(str,"%d号玩家%s被诅咒,轮空两回合。\n", p, name[p-1]);
                showMessage(str);
            }
        } else if (p==0){
            flag = 0;
            sprintf(str,"退出魔法屋。\n");
            showMessage(str);
            //退出
        } else {
            sprintf(str,"输入错误，请重新输入\n");
            showMessage(str);
        }
    } while (flag);
}
