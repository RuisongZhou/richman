#include "judge.h"
#include "building.h"
#include "action.h"
#include "map.h"
#include <stdlib.h>
#include <stdio.h>

static char str[BUF_SIZE];

void getin_hospital(GAME* g){
    g->players[g->playerIndex].hospital_days = SLEEP_TIME_HOSPITAL;
    char* name = &g->players[g->playerIndex].name;
    g->players[g->playerIndex].index = HOSPITAL_POS;
    sprintf(str,"玩家%c, 你触发了炸弹进入医院，住院%d天\n", *name, SLEEP_TIME_HOSPITAL);
    showMessage(str);
}
void getin_police(GAME* g){
    g->players[g->playerIndex].police_days = SLEEP_TIME_PRISON;
    char* name = &g->players[g->playerIndex].name;
    printf("玩家%c, 你已被捕，入狱%d天\n", *name, SLEEP_TIME_PRISON);
}
void getin_gifthouse(GAME* g){
    int n;
    sprintf(str,"欢迎来到礼品屋!\n输入1来获得2000元钱\n输入2来获得200点数\n输入3来获得财神的祝福\n");
    showMessage(str);
    scanf("%d",&n);
    switch (n)
    {
    case 1:
        g->players[g->playerIndex].money+=2000;
        break;
    case 2:
        g->players[g->playerIndex].point+=200;
        break;
    case 3:
        g->players[g->playerIndex].bless_days=5;
        sprintf(str,"财神附身，可免过路费5天\n");
        showMessage(str);
        break;
    default:
        break;
    }
}
void getin_toolhouse(GAME* g){
    int n1,n2,n3,num,price;
    char ch,n;
    sprintf(str,"欢迎来到工具屋!\n");
    showMessage(str);
    do
    {
    CIR:
        sprintf(str,"输入1购买炸弹(50点)\n输入2购买路障(50点)\n输入3购买机器人(30点)\n输入f来离开工具屋\n");
        showMessage(str);
        scanf("%c",&n);
        switch (n)
        {
        case '1':
            g->players[g->playerIndex].point-=50;
            g->players[g->playerIndex].gift[0]+=1;
            n1=g->players[g->playerIndex].gift[0];
            sprintf(str,"你买了一个炸弹，现在你有%d个炸弹\n",n1);
            showMessage(str);
            break;
        case '2':
            g->players[g->playerIndex].point-=50;
            g->players[g->playerIndex].gift[1]+=1;
            n2=g->players[g->playerIndex].gift[1];
            sprintf(str,"你买了一个路障，现在你有%d个路障k\n",n2);
            showMessage(str);
            break;
        case '3':
            g->players[g->playerIndex].point-=30;
            g->players[g->playerIndex].gift[2]+=1;
            n3=g->players[g->playerIndex].gift[2];
            sprintf(str,"你买了一个机器人，现在你有%d个机器人\n",n3);
            showMessage(str);
            break;
        case 'f'://f的ascii值
            break;
        default:
            goto CIR;
        }
    sprintf(str,"请输入任意键继续购买，按f离开\n");
    showMessage(str);
    scanf("%c",&ch);
    if(ch == 'f') break;
    } while (g->players[g->playerIndex].point > 0 && n1+n2+n3 <= 10);
    sprintf(str,"you have %d bomb\nyou have %d block\nyou have %d robot\n",g->players[g->playerIndex].gift[0],g->players[g->playerIndex].gift[1],g->players[g->playerIndex].gift[2]);
    showMessage(str);
}

void getin_house(GAME *g)
{
    int owner = g->map.local[g->players[g->playerIndex].index].belong;
    int money = g->players[g->playerIndex].money;
    int price = g->map.local[g->players[g->playerIndex].index].cost;
    bool state;
    if(owner == -1){    //无人土地

        sprintf(str, "此块土地无人拥有，请问是否购买？土地价格：%d\n你拥有的金钱为:%d\n购买请按Y，不购买请按N\n",price,money );
        showMessage(str);
        char operation[10];
        scanf("%s",operation);
        char res = judgeYN(operation);
        if (res == 'Y'){
            state = buyHouse(g);
            if (state){
                sprintf(str,"购买成功，第%d号土地归%d号玩家%c所有.\n",g->players[g->playerIndex].index, g->players[g->playerIndex].id ,g->players[g->playerIndex].name);

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
            sprintf(str,"此块土地是你的，目前等级为满级\n" );
            showMessage(str);
        } else {
            sprintf(str,"此块土地是你的，请问是否升级？升级价格：%d\n你拥有的金钱为:%d\n购买请按Y，不购买请按N\n",price, money );
            showMessage(str);
            char operation[10];
            scanf("%s",operation);
            char res = judgeYN(operation);
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
        sprintf(str,"财神附体，无需交钱。\n财神附体剩余轮数: %d\n", g->players[g->playerIndex].bless_days);
        showMessage(str);
    } else {    //交钱
        state = payfees(g);
        int cost = price*( g->map.local[g->players[g->playerIndex].index].level +1);
        money = g->players[g->playerIndex].money;
        if(state){
            sprintf(str,"此块地玩家归%d号玩家所有，扣费%d元，剩余%d元", owner, cost/2, money);
        } else {
            sprintf(str,"%d号玩家破产!退出游戏.\n", g->players[g->playerIndex].id);
        }
        showMessage(str);
    }
}