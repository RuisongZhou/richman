#include "command_exec.h"
#include "map.h"
#include "initialize.h"
#include "tools.h"
#include "action.h"
#include <stdlib.h>
int name2id(char ch, GAME *g){
    int i;
    for(i=0; i<g->player_num; i++){
        if(ch==g->players[i].name){
            break;
        }
        else{
            continue;
        }
    }
    return i;
}
int command_exec(Command *cmd, GAME *g)
{
  if(cmd==NULL){
    return 0;
  }
  switch(cmd->params[0]) {
      case COMMAND_ROLL_INDEX:{
          playerMove(g, 0, 0);
          showSystemMessage("roll handler.");
          break;
      }
      case COMMAND_DUMP_INDEX:{
          debug_dump(g);
          showSystemMessage("dump handler.");
          break;
      }
      case COMMAND_QUIT_INDEX:{
          quit();
          exit(-1);
      }
      case COMMAND_RESET_INDEX:{
          initMap(g);
          showSystemMessage("reset handler.");
          break;
      }
      case COMMAND_STEP_INDEX:{
          showSystemMessage("step handler.");
          playerMove(g, cmd->params[1], 1);
          drawMap(g);
          break;
      }
      case COMMAND_SELL_INDEX:{
          /* sell n */
          sellHouse(g, cmd->params[1]);
          drawMap(g);
          showSystemMessage("sell exec success.");
          break;
      }
      case COMMAND_BLOCK_INDEX:{
          /* block n[-10, 10] */
          set_block(cmd->params[1] ,g->players[g->playerIndex].index, g);
          drawMap(g);
          showSystemMessage("block exec success.");
          break;
      }
      case COMMAND_BOMB_INDEX:{
          set_bomb(cmd->params[1], g->players[g->playerIndex].index, g);
          drawMap(g);
          showSystemMessage("bomb exec success.");
          break;
      }
      case COMMAND_ROBOT_INDEX:{
          /* robot */
          set_robot(g->players[g->playerIndex].index, g);
          drawMap(g);
          showSystemMessage("robot exec success.");
          break;
      }
      case COMMAND_QUERY_INDEX:{
          /* query */
          showQuery(g);
          showSystemMessage("query exec success.");
          break;
      }
      case COMMAND_HELP_INDEX:{
          /* help */
          showHelp();
          break;
      }
      case COMMAND_PRESET_INDEX:{
          switch(cmd->params[1]){
              case COMMAND_PRESET_SUBCOMMAND_PLAYER_INDEX:{
                  /* preset player QASJ */
                  char *temp = NULL;
                  temp = (char *)calloc(cmd->length-2+1, sizeof(char));
                  temp[0] = '0' + cmd->length-2;
                  for(int i=0; i<cmd->length-2; i++){
                      temp[i+1] = '0' + cmd->params[i+2];
                  }
                  init_reset(g, temp);
                  showSystemMessage("command player handler.");
                  drawMap(g);
                  break;
              }
              case COMMAND_PRESET_SUBCOMMAND_WHERE_INDEX:{
                  /* preset where QASJ n */

                  g->players[name2id(cmd->params[2], g)].index = cmd->params[3];
                  drawMap(g);
                  showSystemMessage("preset where exec success.");
                  break;
              }
              case COMMAND_PRESET_SUBCOMMAND_FOND_INDEX:{
                  /* preset fond QASJ n */
                  
                  g->players[name2id(cmd->params[2], g)].money = cmd->params[3];
                  showSystemMessage("preset fond exec success.");
                  break;
              }
              case COMMAND_PRESET_SUBCOMMAND_POINTS_INDEX:{
                  /* preset fond QASJ n */
                  g->players[name2id(cmd->params[2], g)].point = cmd->params[3];
                  showSystemMessage("preset points exec success.");
                  break;
              }
              case COMMAND_PRESET_SUBCOMMAND_BLOCK_INDEX:{
                  /* preset block QASJ n */
                  g->players[name2id(cmd->params[2], g)].gift[1] = cmd->params[3];
                  showSystemMessage("preset block exec success.");
                  break;
              }
              case COMMAND_PRESET_SUBCOMMAND_BOMB_INDEX:{
                  g->players[name2id(cmd->params[2], g)].gift[0] = cmd->params[3];
                  showSystemMessage("preset bomb exec success.");
                  break;
              }
              case COMMAND_PRESET_SUBCOMMAND_ROBOT_INDEX:{
                  g->players[name2id(cmd->params[2], g)].gift[2] = cmd->params[3];
                  showSystemMessage("preset robot exec success.");
                  break;
              }
              case COMMAND_PRESET_SUBCOMMAND_HOSPITAL_INDEX:{
                  /* preset hospital QASJ n */
                  g->players[name2id(cmd->params[2], g)].hospital_days = cmd->params[3];
                  g->players[name2id(cmd->params[2], g)].police_days = 0;
                  g->players[name2id(cmd->params[2], g)].index = HOSPITAL_POS;
                  drawMap(g);
                  showSystemMessage("preset hospital exec success.");
                  break;
              }
              case COMMAND_PRESET_SUBCOMMAND_PRISON_INDEX:{
                  g->players[name2id(cmd->params[2], g)].police_days = cmd->params[3];
                  g->players[name2id(cmd->params[2], g)].hospital_days = 0;
                  g->players[name2id(cmd->params[2], g)].index = PRISON_POS;
                  drawMap(g);
                  showSystemMessage("preset prison exec success.");
                  break;
              }
              case COMMAND_PRESET_SUBCOMMAND_BOMB_OR_NOT_INDEX:{
                  /* preset bomb_or_not index */
                  g->map.local[cmd->params[2]].bomb ^= 1;
                  drawMap(g);
                  showSystemMessage("preset bomb_or_not exec success.");
                  break;
              }
              case COMMAND_PRESET_SUBCOMMAND_BLOCK_OR_NOT_INDEX:{
                  g->map.local[cmd->params[2]].block ^= 1;
                  drawMap(g);
                  showSystemMessage("preset block_or_not exec success.");
                  break;
              }
              case COMMAND_PRESET_SUBCOMMAND_LOC_INDEX:{
                  /* preset loc WHERE QASJ LEVEL */
                  g->players[name2id(cmd->params[3], g)].house_num+=1;
                  g->players[name2id(cmd->params[3], g)].house_index[g->players[name2id(cmd->params[3], g)].house_num-1] = cmd->params[2];
                  g->map.local[cmd->params[2]].level = cmd->params[4];
                  showSystemMessage("preset loc exec success.");
                  break;
              }
              case COMMAND_PRESET_SUBCOMMAND_BLESS_INDEX:{
                  /* preset bless QASJ [0-5] */
                  g->players[name2id(cmd->params[2], g)].bless_days = cmd->params[3];
                  showSystemMessage("preset bless exec success.");
                  break;
              }
              case COMMAND_PRESET_SUBCOMMAND_ROUNDS_INEDX:{
                  /* TODO: confirm preset rounds action */
                    changeStatusWithSetRounds(g, cmd->params[2]);
                  showSystemMessage("preset rounds exec success.");
                  break;
              }
              case COMMAND_PRESET_SUBCOMMAND_CLEAR_INDEX:{
                  /* preset clear loc */
                  if(g->map.local[cmd->params[2]].attr==1){
                      for(int i=0; i<g->players[g->map.local[cmd->params[2]].belong].house_num; i++){
                          if(g->players[g->map.local[cmd->params[2]].belong].house_index[i]==cmd->params[2]){
                              for(int j=i; j<g->players[g->map.local[cmd->params[2]].belong].house_num; j++){
                                  g->players[g->map.local[cmd->params[2]].belong].house_index[j] = g->players[g->map.local[cmd->params[2]].belong].house_index[j+1];
                              }
                              break;
                          }
                      }
                      g->players[g->map.local[cmd->params[2]].belong].house_num -= 1;
                      g->map.local[cmd->params[2]].level = 0;
                      g->map.local[cmd->params[2]].belong = 0;
                      g->map.local[cmd->params[2]].block = 0;
                      g->map.local[cmd->params[2]].bomb = 0;
                      showSystemMessage("preset clear command exec success.");
                      break;
                  }
                  else{
                      showSystemMessage("this is not a house.");
                      break;
                  }
                  
              }
              case COMMAND_PRESET_SUBCOMMAND_IS_BANKRUPT_INDEX:{
                  /* preset is_bankrupt QASJ 0||1 */
                  /* TODO: comfirm the is_bankrupt function. */
                  if(cmd->params[3]==1){
                      int tmp = g->playerIndex;
                      g->playerIndex = name2id(cmd->params[2], g);
                      bankrupt(g);
                  }
                  else{
                      /* TODO: add handler of params=0 */
                  }
                  showSystemMessage("preset is_bankrupt exec success.");
                  break;
              }
              case COMMAND_PRESET_SUBCOMMAND_NEXTPLAYER_INDEX:{
                  g->playerIndex = name2id(cmd->params[2], g);
                  drawMap(g);
                  showSystemMessage("preset nextplayer exec success.");
                  break;
              }
              default:{
                  showSystemMessage("preset with unknown subcommand.");
                  break;
              }
          }
          break;
      }
      default:
          showSystemMessage("unknown command.");
          break;
  }
  return 0;
}
