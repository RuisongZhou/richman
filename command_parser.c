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
        return -1;
    }

    *target = 0;

    if(str[0]=='-'){
        if(strlen(str)>6){
            showMessage("Warning: too long inputs.");
            return -1;
        }
    }
    else{
        if(strlen(str)>5){
            showMessage("Warning: too long inputs.");
            return -1;
        }
    }
    int minus = 1;

    if(str[0]=='-'){
        minus = -1;
        str++;
    }

    for(int i=0; i<strlen(str); i++){
        if(str[i]<'0' || str[i]>'9'){
            showMessage("Warning: Input Must Be Int.\n");
            return -1;
        }
        *target = (*target) * 10 + str[i] - '0';
    }

    *target = (*target) * minus;
    return 1;
}
void GetCommandIndex(Command *command, char **command_input){
    switch(command->length) {
        case 1: {
            /* process level one command */
            if (strcmp(command_input[0], COMMAND_ROLL) == 0){
                command->params[0] = COMMAND_ROLL_INDEX;
                return;
            }
            if (strcmp(command_input[0], COMMAND_DUMP) == 0){
                command->params[0] = COMMAND_DUMP_INDEX;
                return;
            }
            if (strcmp(command_input[0], COMMAND_QUIT) == 0){
                command->params[0] = COMMAND_QUIT_INDEX;
                return;
            }
            if (strcmp(command_input[0], COMMAND_RESET) == 0 && IS_DEBUG){
                command->params[0] = COMMAND_RESET_INDEX;
                return;
            }
            command->length = -1;
            return;
        }
        case 2: {
            /* process level two command */

            /* STEP COMMAND PARSER */
            if(strcmp(command_input[0], COMMAND_STEP) == 0 && IS_DEBUG){
                command->params[0] = COMMAND_STEP_INDEX;
//                printf("%s\n", command_input[1]);
//                printf("%d\n", strlen(command_input[1]));
                if(str2int(command_input[1], (command->params+1))==-1){
                    command->length = -1;
                }
                else{
//                    printf("parser number:%d\n", *(command->params+1));
                }
                if(command->params[1]<1 || command->params[1]>6){
                    showMessage("Step Command Only support int [1~6].\n");
                }
                return;
            }
            command->length = -1;
            return;
        }
        case 3: {
            /* process level three command */

            /* Preset Player Command Parser */
            if (strcmp(command_input[0], COMMAND_PRESET) == 0 && IS_DEBUG){
                command->params[0] = COMMAND_PRESET_INDEX;
                if(strcmp(command_input[1], COMMAND_PRESET_SUBCOMMAND_PLAYER) == 0){
                    command->params[1] = COMMAND_PRESET_SUBCOMMAND_PLAYER_INDEX;

                    /* 检测长度错误 */
                    if(strlen(command_input[2])>4 || strlen(command_input[2])<0){
                        showMessage("Error Input.");
                        command->length = -1;
                        return;
                    }
                    /* 检测输入错误和重复错误 */
                    for(int i=0; i<strlen(command_input[2])-1; i++) {
                        char ch = command_input[2][i];
                        if (ch != 'Q' && ch != 'A' && ch != 'S' && ch != 'J') {
                            showMessage("Cannot identify rols.");
                            command->length = -1;
                            return;
                        }
                        for (int j = i + 1; j < strlen(command_input[2]); j++) {
                            if (ch == command_input[2][j]) {
                                showMessage("No repeate Input Please.");
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
                                showMessage("Some thing wrong. Game will exit now.");
                                exit(-1);
                            }
                        }
                    }
                    return;
                }
            }
            command->length = -1;
            return;
        }
        case 4: {
            /* process level four command */
            command->length = -1;
            return;
        }
        case 5: {
            /* process leve five command */
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
    /* for fgets: fgets will read \n */

    Command *command = (Command *)calloc(1, sizeof(Command));
    command->length = 0;
    command->params = NULL;

    if(strlen(command_input)==0){
        printf("no command get\n");
//        showMessage("No command found!\n");
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
        printf("command error");
//        showMessage("Command Error.\n");
        free(command);
        return NULL;
    }
    /* log for debug */
//    for(int i=0; i<command->length; i++){
//        printf("%d ", command->params[i]);
//    }
//    printf("\n");
    return command;
}
