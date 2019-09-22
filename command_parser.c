//
// Created by 杨澍生 on 2019-09-14.
//

#include "command_parser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "map.h"

int str2int(char *str, int *target){
    if(str==NULL){
        return 0;
    }

    *target = 0;

    if(str[0]=='-'){
        if(strlen(str)>6){
            showSystemMessage("Warning: too long inputs.");
            return 0;
        }
    }
    else{
        if(strlen(str)>5){
            showSystemMessage("Warning: too long inputs.");
            return 0;
        }
    }
    int minus = 1;

    if(str[0]=='-'){
        minus = -1;
        ++str;
    }

    for(int i=0; i<strlen(str); i++){
        if(str[i]<'0' || str[i]>'9'){
            showSystemMessage("Warning: Input Must Be Int.");
            return 0;
        }
        *target = (*target) * 10 + str[i] - '0';
    }

    *target = (*target) * minus;
    return 1;
}
char *convert_to_low_case(char *str){
    char *temp = str;
    while((*str)!='\0'){
        if(*str>='A' && *str<='Z')
            (*str) = (*str)+32;
        str++;
    }
    return temp;
}
int is_role(char ch){
    switch(ch)
    {
    case P_JBB:
        return P_JBB;
    case P_SXM:
        return P_SXM;
    case P_QFR:
        return P_QFR;
    case P_ATB:
        return P_ATB;
    default:
        return -1;
    }
}
void GetCommandIndex(Command *command, char **command_input){
    switch(command->length) {
        case 1: {
            /* process level one command */
            if (strcmp(convert_to_low_case(command_input[0]), COMMAND_ROLL) == 0){
                command->params[0] = COMMAND_ROLL_INDEX;
                return;
            }
            if (strcmp(convert_to_low_case(command_input[0]), COMMAND_DUMP) == 0){
                command->params[0] = COMMAND_DUMP_INDEX;
                return;
            }
            if (strcmp(convert_to_low_case(command_input[0]), COMMAND_QUIT) == 0){
                command->params[0] = COMMAND_QUIT_INDEX;
                return;
            }
            if (strcmp(convert_to_low_case(command_input[0]), COMMAND_ROBOT) == 0){
                command->params[0] = COMMAND_ROBOT_INDEX;
                return;
            }
            if (strcmp(convert_to_low_case(command_input[0]), COMMAND_RESET) == 0 && IS_DEBUG){
                command->params[0] = COMMAND_RESET_INDEX;
                return;
            }
            if(strcmp(convert_to_low_case(command_input[0]), COMMAND_QUERY) == 0){
                command->params[0] = COMMAND_QUERY_INDEX;
                return;
            }
            if(strcmp(convert_to_low_case(command_input[0]), COMMAND_HELP) == 0){
                command->params[0] = COMMAND_HELP_INDEX;
                return;
            }
            if(strcmp(convert_to_low_case(command_input[0]), COMMAND_SHOW_ME_THE_MONEY) == 0){
                command->params[0] = COMMAND_SHOW_ME_THE_MONEY_INDEX;
                return;
            }
            command->length = -1;
            return;
        }
        case 2: {
            /* process level two command */

            /* STEP COMMAND PARSER */
            if(strcmp(convert_to_low_case(command_input[0]), COMMAND_STEP) == 0){
                command->params[0] = COMMAND_STEP_INDEX;
                if(str2int(command_input[1], (command->params+1))==0){
                    command->length = -1;
                    return;
                }
                else{
                    ;
                }
                if(command->params[1]<1 || command->params[1]>6){
                    showSystemMessage("Step Command Only support int [1~6].");
                    command->length = -1;
                    return;
                }
                return;
            }
            if(strcmp(convert_to_low_case(command_input[0]), COMMAND_SELL) == 0){
                showSystemMessage("sell catched.");
                command->params[0] = COMMAND_SELL_INDEX;

                if(str2int(command_input[1], &(command->params[1]))){
                    if(command->params[1]<0 || command->params[1]>69){
                        showSystemMessage("[0, 69].");
                        command->length = -1;
                        return;
                    }
                    showSystemMessage("sell catched.");
                    return;
                }
                command->length = -1;
                return;
            }
            if(strcmp(convert_to_low_case(command_input[0]), COMMAND_BLOCK) == 0){
                showSystemMessage("block catched.");
                command->params[0] = COMMAND_BLOCK_INDEX;

                if(str2int(command_input[1], &(command->params[1]))){
                    if(command->params[1]<-10 || command->params[1]>10){
                        showSystemMessage("[-10, 10].");
                        command->length = -1;
                        return;
                    }
                    showSystemMessage("block n catched.");
                    return;
                }
                command->length = -1;
                return;
            }
            if(strcmp(convert_to_low_case(command_input[0]), COMMAND_BOMB) == 0){
                showSystemMessage("bomb catched.");
                command->params[0] = COMMAND_BOMB_INDEX;

                if(str2int(command_input[1], &(command->params[1]))){
                    if(command->params[1]<-10 || command->params[1]>10){
                        showSystemMessage("[-10, 10].");
                        command->length = -1;
                        return;
                    }
                    showSystemMessage("bomb n catched.");
                    return;
                }
                command->length = -1;
                return;
            }
            command->length = -1;
            return;
        }
        case 3: {
            /* process level three command */

            /* Preset Player Command Parser */
            if (strcmp(convert_to_low_case(command_input[0]), COMMAND_PRESET) == 0 && IS_DEBUG){
                if(IS_DEBUG)
                    showSystemMessage("preset command caught.");
                command->params[0] = COMMAND_PRESET_INDEX;
                if(strcmp(convert_to_low_case(command_input[1]), COMMAND_PRESET_SUBCOMMAND_PLAYER) == 0){
                    if(IS_DEBUG) showSystemMessage("preset player catched.");
                    command->params[1] = COMMAND_PRESET_SUBCOMMAND_PLAYER_INDEX;

                    /* 检测长度错误 */
                    if(strlen(command_input[2])>4 || strlen(command_input[2])<0){
                        showSystemMessage("Error Input.");
                        command->length = -1;
                        return;
                    }
                    /* 检测输入错误和重复错误 */
                    for(int i=0; i<strlen(command_input[2])-1; i++) {
                        char ch = command_input[2][i];
                        if (ch != 'Q' && ch != 'A' && ch != 'S' && ch != 'J') {
                            showSystemMessage("Cannot identify rols.");
                            command->length = -1;
                            return;
                        }
                        for (int j = i + 1; j < strlen(command_input[2]); j++) {
                            if (ch == command_input[2][j]) {
                                showSystemMessage("No repeate Input Please.");
                                command->length = -1;
                                return;
                            }
                        }
                    }

                    command->length += strlen(command_input[2]) - 1;
                    char *tmp = command_input[2];
                    command->params = (int *)realloc(command->params, command->length * sizeof(int));
                    for(int i=command->length-strlen(command_input[2]); i<command->length; i++){
                        switch(command_input[2][i-(command->length - strlen(command_input[2]))]){
                            case 'Q':{
                                command->params[i] = 1;
                                break;
                            }
                            case 'A':{
                                command->params[i] = 2;
                                break;
                            }
                            case 'S':{
                                command->params[i] = 3;
                                break;
                            }
                            case 'J':{
                                command->params[i] = 4;
                                break;
                            }
                            default:{
                                /* 理论上不应该进入这里，之前的错误检测已经保证不会出现错误情况，写这个是为了以防万一 */
                                showSystemMessage("Some thing wrong. Game will exit now.");
                                exit(-1);
                            }
                        }
                    }
                    return;
                }
                if(strcmp(convert_to_low_case(command_input[1]), COMMAND_PRESET_SUBCOMMAND_BOMB_OR_NOT) == 0){
                    if(IS_DEBUG) showSystemMessage("preset bomb_or_not catched.");
                    command->params[1] = COMMAND_PRESET_SUBCOMMAND_BOMB_OR_NOT_INDEX;

                    if(str2int(command_input[2], &(command->params[2]))){
                        if(command->params[2]>69 || command->params[2]<0){
                            showSystemMessage("[0, 69].");
                            command->length = -1;
                            return;
                        }
                        showSystemMessage("preset bomb_or_not command catched.");
                        return;
                    }
                    else{
                        command->length = -1;
                        return;
                    }
                }
                if(strcmp(convert_to_low_case(command_input[1]), COMMAND_PRESET_SUBCOMMAND_BLOCK_OR_NOT) == 0){
                    if(IS_DEBUG) showSystemMessage("preset block_or_not catched.");
                    command->params[1] = COMMAND_PRESET_SUBCOMMAND_BLOCK_OR_NOT_INDEX;

                    if(str2int(command_input[2], &(command->params[2]))){
                        if(command->params[2]>69 || command->params[2]<0){
                            showSystemMessage("[0, 69].");
                            command->length = -1;
                            return;
                        }
                        showSystemMessage("preset block_or_not command catched.");
                        return;
                    }
                    else{
                        command->length = -1;
                        return;
                    }
                }
                if(strcmp(convert_to_low_case(command_input[1]), COMMAND_PRESET_SUBCOMMAND_ROUNDS) == 0){
                    /* preset rounds [0-20] */
                    command->params[1] = COMMAND_PRESET_SUBCOMMAND_ROUNDS_INEDX;
                    if(IS_DEBUG) showSystemMessage("preset rounds catched.");
                    if(str2int(command_input[2], &(command->params[2]))){
                        if(command->params[2]>20 || command->params[2]<0){
                            showSystemMessage("[0, 20].");
                            command->length = -1;
                            return;
                        }
                        showSystemMessage("preset rounds success.");
                        return;
                    }
                    else{
                        command->length = -1;
                        return;
                    }
                }
                if(strcmp(convert_to_low_case(command_input[1]), COMMAND_PRESET_SUBCOMMAND_CLEAR) == 0){
                    /* preset clear [0-69] */
                    if(IS_DEBUG) showSystemMessage("preset clear catched.");
                    command->params[1] = COMMAND_PRESET_SUBCOMMAND_CLEAR_INDEX;
                    if(str2int(command_input[2], &(command->params[2]))){
                        if(command->params[2]>69 || command->params[2]<0){
                            showSystemMessage("[0, 69].");
                            command->length = -1;
                            return;
                        }
                        showSystemMessage("preset clear success.");
                        return;
                    }
                    else{
                        command->length = -1;
                        return;
                    }
                }
                if(strcmp(convert_to_low_case(command_input[1]), COMMAND_PRESET_SUBCOMMAND_NEXTPLAYER) == 0){
                    /* preset nextplayer [QASJ] */
                    if(IS_DEBUG) showSystemMessage("preset nextplayer catched.");
                    command->params[1] = COMMAND_PRESET_SUBCOMMAND_NEXTPLAYER_INDEX;

                    if(strlen(command_input[2])!=1){
                        showSystemMessage("single role required.");
                        command->length = -1;
                        return;
                    }
                    if(is_role(command_input[2][0])){
                        command->params[2] = is_role(command_input[2][0]);
                        showSystemMessage("preset nextplayer success.");
                        return;
                    }
                    else{
                        showSystemMessage("wrong role.");
                        command->length = -1;
                        return;
                    }
                }
            }
            command->length = -1;
            return;
        }
        case 4: {
            /* process level four command */
            if (strcmp(convert_to_low_case(command_input[0]), COMMAND_PRESET) == 0 && IS_DEBUG){
                if(IS_DEBUG)
                    showSystemMessage("preset command caught.");
                command->params[0] = COMMAND_PRESET_INDEX;
                if(strcmp(convert_to_low_case(command_input[1]), COMMAND_PRESET_SUBCOMMAND_WHERE) == 0){
                    if(IS_DEBUG) showSystemMessage("preset where catched.");
                    command->params[1] = COMMAND_PRESET_SUBCOMMAND_WHERE_INDEX;

                    if(strlen(command_input[2])!=1){
                        showSystemMessage("preset where command can only do for a role.");
                    }
                    switch(command_input[2][0]){
                        case P_ATB:{
                            command->params[2] = P_ATB;
                            break;
                        }
                        case P_JBB:{
                            command->params[2] = P_JBB;
                            break;
                        }
                        case P_SXM:{
                            command->params[2] = P_SXM;
                            break;
                        }
                        case P_QFR:{
                            command->params[2] = P_QFR;
                            break;
                        }
                        default:{
                            showSystemMessage("please input correct role.");
                            command->length = -1;
                            return;
                        }
                    }
                    if(!str2int(command_input[3], &(command->params[3]))){
                        command->length = -1;
                        return;
                    }
                    if(command->params[3]<0 || command->params[3]>69){
                        showSystemMessage("loc should between [0,69].");
                        command->length = -1;
                        return;
                    }
                    else{
                        showSystemMessage("preset where command success.");
                        return;
                    }
                    return;
                }
                if(strcmp(convert_to_low_case(command_input[1]), COMMAND_PRESET_SUBCOMMAND_FUND) == 0){
                    if(IS_DEBUG)
                        showSystemMessage("preset fund command catched.");
                    command->params[1] = COMMAND_PRESET_SUBCOMMAND_FUND_INDEX;

                    if(strlen(command_input[2])!=1){
                        showSystemMessage("please only on roles.");
                        command->length = -1;
                        return;
                    }
                    if(is_role(command_input[2][0])){
                        command->params[2] = is_role(command_input[2][0]);
                    }
                    else{
                        showSystemMessage("wrong role.");
                        command->length = -1;
                        return;
                    }

                    if(str2int(command_input[3], &(command->params[3]))){
                        if(command->params[3]<0 || command->params[3]>50000){
                            showSystemMessage("[0, 50000].");
                            command->length = -1;
                            return;
                        }
                        showSystemMessage("preset fund command success.");
                        return;
                    }
                }
                if(strcmp(convert_to_low_case(command_input[1]), COMMAND_PRESET_SUBCOMMAND_POINTS) == 0){
                    if(IS_DEBUG) showSystemMessage("preset points catched.");
                    command->params[1] = COMMAND_PRESET_SUBCOMMAND_POINTS_INDEX;

                    if(strlen(command_input[2])!=1){
                        showSystemMessage("should be single role.");
                        command->length = -1;
                        return;
                    }
                    if(is_role(command_input[2][0])){
                        command->params[2] = is_role(command_input[2][0]);
                    }
                    else{
                        showSystemMessage("wrong roles.");
                        command->length = -1;
                        return;
                    }
                    if(str2int(command_input[3], &(command->params[3]))){
                        if(command->params[3]>200 || command->params[3]<0){
                            showSystemMessage("[0, 200].");
                            command->length = -1;
                            return;
                        }
                        showSystemMessage("preset points command catched.");
                        return;
                    }
                    else{
                        command->length = -1;
                        return;
                    }
                }
                if(strcmp(convert_to_low_case(command_input[1]), COMMAND_PRESET_SUBCOMMAND_BLOCK) == 0){
                    if(IS_DEBUG) showSystemMessage("preset block catched.");
                    command->params[1] = COMMAND_PRESET_SUBCOMMAND_BLOCK_INDEX;

                    if(strlen(command_input[2])!=1){
                        showSystemMessage("should be single role.");
                        command->length = -1;
                        return;
                    }
                    if(is_role(command_input[2][0])){
                        command->params[2] = is_role(command_input[2][0]);
                    }
                    else{
                        showSystemMessage("wrong roles.");
                        command->length = -1;
                        return;
                    }
                    if(str2int(command_input[3], &(command->params[3]))){
                        if(command->params[3]>10 || command->params[3]<0){
                            showSystemMessage("[0, 10].");
                            command->length = -1;
                            return;
                        }
                        showSystemMessage("preset block command catched.");
                        return;
                    }
                    else{
                        command->length = -1;
                        return;
                    }
                }
                if(strcmp(convert_to_low_case(command_input[1]), COMMAND_PRESET_SUBCOMMAND_BOMB) == 0){
                    if(IS_DEBUG) showSystemMessage("preset bomb catched.");
                    command->params[1] = COMMAND_PRESET_SUBCOMMAND_BOMB_INDEX;

                    if(strlen(command_input[2])!=1){
                        showSystemMessage("should be single role.");
                        command->length = -1;
                        return;
                    }
                    if(is_role(command_input[2][0])){
                        command->params[2] = is_role(command_input[2][0]);
                    }
                    else{
                        showSystemMessage("wrong roles.");
                        command->length = -1;
                        return;
                    }
                    if(str2int(command_input[3], &(command->params[3]))){
                        if(command->params[3]>10 || command->params[3]<0){
                            showSystemMessage("[0, 10].");
                            command->length = -1;
                            return;
                        }
                        showSystemMessage("preset bomb command catched.");
                        return;
                    }
                    else{
                        command->length = -1;
                        return;
                    }
                }
                if(strcmp(convert_to_low_case(command_input[1]), COMMAND_PRESET_SUBCOMMAND_ROBOT) == 0){
                    if(IS_DEBUG) showSystemMessage("preset robot catched.");
                    command->params[1] = COMMAND_PRESET_SUBCOMMAND_ROBOT_INDEX;

                    if(strlen(command_input[2])!=1){
                        showSystemMessage("should be single role.");
                        command->length = -1;
                        return;
                    }
                    if(is_role(command_input[2][0])){
                        command->params[2] = is_role(command_input[2][0]);
                    }
                    else{
                        showSystemMessage("wrong roles.");
                        command->length = -1;
                        return;
                    }
                    if(str2int(command_input[3], &(command->params[3]))){
                        if(command->params[3]>10 || command->params[3]<0){
                            showSystemMessage("[0, 10].");
                            command->length = -1;
                            return;
                        }
                        showSystemMessage("preset robot command catched.");
                        return;
                    }
                    else{
                        command->length = -1;
                        return;
                    }
                }
                if(strcmp(convert_to_low_case(command_input[1]), COMMAND_PRESET_SUBCOMMAND_HOSPITAL) == 0){
                    if(IS_DEBUG) showSystemMessage("preset hospital catched.");
                    command->params[1] = COMMAND_PRESET_SUBCOMMAND_HOSPITAL_INDEX;

                    if(strlen(command_input[2])!=1){
                        showSystemMessage("should be single role.");
                        command->length = -1;
                        return;
                    }
                    if(is_role(command_input[2][0])){
                        command->params[2] = is_role(command_input[2][0]);
                    }
                    else{
                        showSystemMessage("wrong roles.");
                        command->length = -1;
                        return;
                    }
                    if(str2int(command_input[3], &(command->params[3]))){
                        if(command->params[3]>3 || command->params[3]<0){
                            showSystemMessage("[0, 3].");
                            command->length = -1;
                            return;
                        }
                        showSystemMessage("preset hospital command catched.");
                        return;
                    }
                    else{
                        command->length = -1;
                        return;
                    }
                }
                if(strcmp(convert_to_low_case(command_input[1]), COMMAND_PRESET_SUBCOMMAND_PRISON) == 0){
                    if(IS_DEBUG) showSystemMessage("preset prison catched.");
                    command->params[1] = COMMAND_PRESET_SUBCOMMAND_PRISON_INDEX;

                    if(strlen(command_input[2])!=1){
                        showSystemMessage("should be single role.");
                        command->length = -1;
                        return;
                    }
                    if(is_role(command_input[2][0])){
                        command->params[2] = is_role(command_input[2][0]);
                    }
                    else{
                        showSystemMessage("wrong roles.");
                        command->length = -1;
                        return;
                    }
                    if(str2int(command_input[3], &(command->params[3]))){
                        if(command->params[3]>2 || command->params[3]<0){
                            showSystemMessage("[0, 2].");
                            command->length = -1;
                            return;
                        }
                        showSystemMessage("preset prison command catched.");
                        return;
                    }
                    else{
                        command->length = -1;
                        return;
                    }
                }
                if(strcmp(convert_to_low_case(command_input[1]), COMMAND_PRESET_SUBCOMMAND_BLESS) == 0){
                    if(IS_DEBUG) showSystemMessage("preset bless catched.");
                    command->params[1] = COMMAND_PRESET_SUBCOMMAND_BLESS_INDEX;

                    if(strlen(command_input[2])!=1){
                        showSystemMessage("should be single role.");
                        command->length = -1;
                        return;
                    }
                    if(is_role(command_input[2][0])){
                        command->params[2] = is_role(command_input[2][0]);
                    }
                    else{
                        showSystemMessage("wrong roles.");
                        command->length = -1;
                        return;
                    }
                    if(str2int(command_input[3], &(command->params[3]))){
                        if(command->params[3]>5 || command->params[3]<0){
                            showSystemMessage("[0, 5].");
                            command->length = -1;
                            return;
                        }
                        showSystemMessage("preset bless command catched.");
                        return;
                    }
                    else{
                        command->length = -1;
                        return;
                    }
                }
                if(strcmp(convert_to_low_case(command_input[1]), COMMAND_PRESET_SUBCOMMAND_IS_BANKRUPT) == 0){
                    /* preset is_bankrupt QASJ 0||1 */
                    if(IS_DEBUG) showSystemMessage("preset is_bankrupt catched.");
                    command->params[1] = COMMAND_PRESET_SUBCOMMAND_IS_BANKRUPT_INDEX;

                    if(strlen(command_input[2])!=1){
                        showSystemMessage("should be single role.");
                        command->length = -1;
                        return;
                    }
                    if(is_role(command_input[2][0])){
                        command->params[2] = is_role(command_input[2][0]);
                    }
                    else{
                        showSystemMessage("wrong roles.");
                        command->length = -1;
                        return;
                    }
                    if(str2int(command_input[3], &(command->params[3]))){
                        if(command->params[3]>1 || command->params[3]<0){
                            showSystemMessage("[0, 1].");
                            command->length = -1;
                            return;
                        }
                        showSystemMessage("preset is_bankrupt command catched.");
                        return;
                    }
                    else{
                        command->length = -1;
                        return;
                    }
                }
            }
            command->length = -1;
            return;
        }
        case 5: {
            /* process leve five command */
            if (strcmp(convert_to_low_case(command_input[0]), COMMAND_PRESET) == 0 && IS_DEBUG){
                if(IS_DEBUG)
                    showSystemMessage("preset command caught.");
                command->params[0] = COMMAND_PRESET_INDEX;
                if(strcmp(convert_to_low_case(command_input[1]), COMMAND_PRESET_SUBCOMMAND_LOC) == 0){
                    if(IS_DEBUG) showSystemMessage("preset loc catched.");
                    command->params[1] = COMMAND_PRESET_SUBCOMMAND_LOC_INDEX;

                    if(!str2int(command_input[2], &(command->params[2]))){
                        command->length = -1;
                        return;
                    }
                    else{
                        if(command->params[2]>69 || command->params[2]<0){
                            showSystemMessage("[0, 69].");
                            command->length = -1;
                            return;
                        }
                    }
                    if(strlen(command_input[3])!=1){
                        showSystemMessage("only one role should be here.");
                        command->length = -1;
                        return;
                    }
                    if(is_role(command_input[3][0])){
                        command->params[3] = is_role(command_input[3][0]);
                    }
                    else{
                        showSystemMessage("wrong role.");
                        command->length = -1;
                        return;
                    }
                    if(str2int(command_input[4], &(command->params[4]))){
                        if(command->params[4]<0 || command->params[4]>3){
                            showSystemMessage("[0, 3].");
                            command->length = -1;
                            return;
                        }
                        showSystemMessage("preset loc catched.");
                        return;
                    }
                    else{
                        command->length = -1;
                        return;
                    }
                }
            }
            command->length = -1;
            return;
        }
        default:
            command->length = -1;
            return;
    }
}

Command *CommandParser(char *command_input){
    command_input[strlen(command_input)-1] = '\0';
    /* for fgets: fgets will read  */

    Command *command = (Command *)calloc(1, sizeof(Command));
    command->length = 0;
    command->params = NULL;

    if(strlen(command_input)==0){
        showSystemMessage("No command found!");
        free(command);
        return NULL;
    }

    char *parse_result = NULL;
    char **split = (char **)calloc(1, sizeof(char *));
    /* parse_result do not need to be free, it is not a alloc memory */

    parse_result = strtok(command_input, " ");

    while(parse_result){
        command->length += 1;
        split = (char **)realloc(split, command->length * sizeof(char *));
        split[command->length-1] = parse_result;
        parse_result = strtok(NULL, " ");
    }
    command->params = (int *)calloc(command->length, sizeof(int));

    GetCommandIndex(command, split);
    if(command->length==-1){
        showSystemMessage("command error.");
        free(command);
        return NULL;
    }
    return command;
}
