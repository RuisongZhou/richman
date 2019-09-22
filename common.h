//
// Created by 周瑞松 on 2019/9/14.
//

#ifndef RICHMAN_COMMON_H
#define RICHMAN_COMMON_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>

#define BUF_SIZE            512
#define MAP_SIZE            70
#define PRISON_POS          49
#define HOSPITAL_POS        14 //以下sleep时间待定
#define SLEEP_TIME_HOSPITAL 3
#define SLEEP_TIME_PRISON   2
#define MAGIC_TIME          2

//#define HOSPITAL    'H'     // hospital
#define HOSPITAL    'P'     // hospital was changed to park
#define TOOLHOUSE   'T'     // tool house
#define SPACE       '0'     // space
#define GIFTHOUSE   'G'     // gift house
#define MAGIC       'M'     // magic house
#define PRISON      'P'     // prison
#define MINERAL     '$'     // mineral area
#define START       'S'     // start area
#define ROADBLOCK   '#'
#define BOMB        '@'

#define P_QFR 'Q'       // 钱夫人
#define P_ATB 'A'       // 阿土伯
#define P_SXM 'S'       // 孙小美
#define P_JBB 'J'       // 金贝贝

// IS_DEBUG 0 表示正常游戏模式，1 表示debug模式
// #define IS_DEBUG                1
int IS_DEBUG;
#define IS_DEBUG_NAME           "管理员——"
#define IS_DEBUG_NAME_LENGTH    8

#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)  

#define COMMAND_ROLL_INDEX      0
#define COMMAND_DUMP_INDEX      1
#define COMMAND_QUIT_INDEX      2
#define COMMAND_RESET_INDEX     3
#define COMMAND_STEP_INDEX      4
#define COMMAND_PRESET_INDEX    5
#define COMMAND_SELL_INDEX      6
#define COMMAND_BLOCK_INDEX     7
#define COMMAND_BOMB_INDEX      8
#define COMMAND_ROBOT_INDEX     9
#define COMMAND_QUERY_INDEX     10
#define COMMAND_HELP_INDEX      11

#define COMMAND_SHOW_ME_THE_MONEY_INDEX 12
#define COMMAND_BLACK_SHEEP_WALL_INDEX 13

#define COMMAND_ROLL    "roll"
#define COMMAND_DUMP    "dump"
#define COMMAND_QUIT    "quit"
#define COMMAND_RESET   "reset"
#define COMMAND_STEP    "step"
#define COMMAND_PRESET  "preset"
#define COMMAND_SELL    "sell"
#define COMMAND_BLOCK   "block"
#define COMMAND_BOMB    "bomb_delete" /* has been deleted by Mrs.Hu */
#define COMMAND_ROBOT   "robot"
#define COMMAND_QUERY   "query"
#define COMMAND_HELP    "help"

#define COMMAND_SHOW_ME_THE_MONEY "show_me_the_money"
#define COMMAND_BLACK_SHEEP_WALL "black_sheep_wall"

#define COMMAND_PRESET_SUBCOMMAND_PLAYER_INDEX          1
#define COMMAND_PRESET_SUBCOMMAND_PLAYER                "players"
#define COMMAND_PRESET_SUBCOMMAND_WHERE_INDEX           2
#define COMMAND_PRESET_SUBCOMMAND_WHERE                 "where"
#define COMMAND_PRESET_SUBCOMMAND_FUND_INDEX            3
#define COMMAND_PRESET_SUBCOMMAND_FUND                  "fund"
#define COMMAND_PRESET_SUBCOMMAND_POINTS_INDEX          4
#define COMMAND_PRESET_SUBCOMMAND_POINTS                "points"
#define COMMAND_PRESET_SUBCOMMAND_BLOCK_INDEX           5
#define COMMAND_PRESET_SUBCOMMAND_BLOCK                 "block"
#define COMMAND_PRESET_SUBCOMMAND_BOMB_INDEX            6
#define COMMAND_PRESET_SUBCOMMAND_BOMB                  "bomb_delete" /* has been deleted by Mrs.Hu */
#define COMMAND_PRESET_SUBCOMMAND_ROBOT_INDEX           7
#define COMMAND_PRESET_SUBCOMMAND_ROBOT                 "robot"
#define COMMAND_PRESET_SUBCOMMAND_HOSPITAL_INDEX        8
#define COMMAND_PRESET_SUBCOMMAND_HOSPITAL              "hospital_delete" /* has been deleted by Mrs.Hu */
#define COMMAND_PRESET_SUBCOMMAND_PRISON_INDEX          9
#define COMMAND_PRESET_SUBCOMMAND_PRISON                "presion_delete" /* has been deleted by Mrs.Hu */
#define COMMAND_PRESET_SUBCOMMAND_BOMB_OR_NOT_INDEX     10
#define COMMAND_PRESET_SUBCOMMAND_BOMB_OR_NOT           "bomb_or_not_delete" /* has been deleted by Mrs.Hu */
#define COMMAND_PRESET_SUBCOMMAND_BLOCK_OR_NOT_INDEX    11
#define COMMAND_PRESET_SUBCOMMAND_BLOCK_OR_NOT          "block_or_not"
#define COMMAND_PRESET_SUBCOMMAND_LOC_INDEX             12
#define COMMAND_PRESET_SUBCOMMAND_LOC                   "loc"
#define COMMAND_PRESET_SUBCOMMAND_BLESS_INDEX           13
#define COMMAND_PRESET_SUBCOMMAND_BLESS                 "bless"
#define COMMAND_PRESET_SUBCOMMAND_ROUNDS_INEDX          14
#define COMMAND_PRESET_SUBCOMMAND_ROUNDS                "rounds"
#define COMMAND_PRESET_SUBCOMMAND_CLEAR_INDEX           15
#define COMMAND_PRESET_SUBCOMMAND_CLEAR                 "clear"
#define COMMAND_PRESET_SUBCOMMAND_IS_BANKRUPT_INDEX     16
#define COMMAND_PRESET_SUBCOMMAND_IS_BANKRUPT           "is_bankrupt"
#define COMMAND_PRESET_SUBCOMMAND_NEXTPLAYER_INDEX      17
#define COMMAND_PRESET_SUBCOMMAND_NEXTPLAYER            "nextplayer"

#define WIDTH 90
#define HEIGHT 35

#define INPUT                   "> "
#define INPUTX                  9
#define INPUTY                  0
#define INPUTLENGTH             2
#define SYSTEMMESSAGE           "SystemMessage: "
#define SYSTEMMESSAGEX          11
#define SYSTEMMESSAGEY          0
#define SYSTEMMESSAGELENGTH     15
#define MESSAGE                 "Message: "
#define MESSAGEX                13
#define MESSAGEY                0
#define MESSAGELENGTH           9
#define ROUND                   "Round"
#define ROUNDX                  3
#define ROUNDY                  12
#define ROUNDLENGTH             6
#define ROUNDCOLOR              'Q'

// 相对路径
#define GAMEMUSIC   "./music/梦幻伊甸园.mp3"
#define STARTMUSIC  "./music/新游戏.mp3"
#define ENDMUSIC    "./music/新游戏.mp3"
#define BREAKMUSIC  "./music/破产.mp3"

#define ENDANIMATIONHEIGHT      130

#define QBOMBX  2
#define QBOMBY  40
#define QBOMB   "持有炸弹数量："
#define QMONEYX 0
#define QMONEYY 40
#define QMONEY  "持有现金金额："
#define QPOINTX 1
#define QPOINTY 40
#define QPOINT  "持有礼品点数："
#define QBLOCKX 3
#define QBLOCKY 40
#define QBLOCK  "持有障碍物数量："
#define QROBOTX 4
#define QROBOTY 40
#define QROBOT  "持有机器娃娃数量："
#define QBLESSX 5
#define QBLESSY 40
#define QBLESS  "财神附身时间："
#define QINDEXX 6
#define QINDEXY 40
#define QINDEX  "当前位置："
#define QHOUSEX 7
#define QHOUSEY 40
#define QHOUSE  "拥有房产："

typedef struct location {
    int x, y; // 点的绘图点
    int attr; // 地图建筑的类型（BEGIN = 0, HOUSE = 1, HOSPITAL = 2, POLICE = 3, GIFTHOUSE = 4, MAGICHOUSE = 5, TOOLHOUSE = 6, MINERAL = 7）
    int level; // 当该location.attr == house的时候启用，记录当前house的等级
    int cost; // 当该location.attr == house的时候启用，记录当前house的购地、升级费用，过路费=level * cost * group
    int belong; // 当该location.attr == house的时候启用，记录当前house的主人id   1~4
    int group; // 当该location.attr == house的时候启用，记录当前house的组别，同组的house需要有相同的group参数（默认为1，当全组的被同一个人购买后置为2）
    bool bomb; // 当前场景是否布置炸弹
    bool block; // 当前场景是否有路障
}LOCATION;

typedef struct map_information {
    LOCATION local[MAP_SIZE]; // 地图场景数组
    int house_index[MAP_SIZE]; // house的相对位置
}MAP_INFOMATION;

typedef struct player {
    int id; // 玩家的id     1~4
    char name; // 玩家的名称
    int index; // 玩家所在的相对位置，索引到map.local[index].x map.local[index].y
    int money; // 玩家的现金
    int point; // 玩家所拥有点数（用于购买道具）
    int house_index[MAP_SIZE]; // 玩家所拥有的house的相对位置
    int house_num; // 玩家所拥有的house的数量
    int gift[3]; // 各种道具持有数量（桶）0-炸弹 1-路障 2-robot
    bool status; // 玩家是否结束游戏（0:继续游戏，1:破产退出游戏）
    int hospital_days; // 玩家住院时间
    int police_days; // 玩家拘留时间
    int bless_days; // 财神持续时间
    int magic_time;  //魔法屋陷害天数
}PLAYER;

typedef struct game {
    int             player_less_num;//当前剩下的玩家数
    int             player_num;     //游戏总玩家数
    int             playerIndex;    // 目前玩家指针
    PLAYER          players[4];     //所有玩家指针
    MAP_INFOMATION  map;            //地图储存
    char            *save_path;     //dump储存路径
    int             rounds;         // 游戏轮数
    pthread_t       music;          // 播放音频的线程
}GAME;

typedef struct command {
    int length;
    int *params;
} Command;

#endif //RICHMAN_STRUCT_H
