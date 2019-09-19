/*
 函数名：command_exec
 作者：  郭一兴
  功能： 处理命令流程
*/

#include "command_exec.h"
#include "map.h"
#include "initialize.h"
#include <stdlib.h>

int command_exec(Command *cmd, GAME *g)
{
  if(cmd==NULL){
    return 0;
  }
  switch(cmd->params[0]) {
      case COMMAND_ROLL_INDEX:{
          printf("command roll got\n");
          playerMove(g, 0, 0);
          break;
      }
      case COMMAND_DUMP_INDEX:{
          printf("command dump got\n");
          debug_dump(g);
          break;
      }
      case COMMAND_QUIT_INDEX:{
          showMessage("Game will quit soon.");
          showMessage("Bye~");
          printf("command quit got\n");
          exit(-1);
      }
      case COMMAND_RESET_INDEX:{
          printf("command reset got\n");
          initMap(g);
          drawMap(g);
          showMessage("this is reset handler.");
          break;
      }
      case COMMAND_STEP_INDEX:{
          printf("command step got \n");
          playerMove(g, cmd->params[1], 1);
          drawMap(g);
          break;
      }
      case COMMAND_PRESET_INDEX:{
          switch(cmd->params[1]){
              case COMMAND_PRESET_SUBCOMMAND_PLAYER_INDEX:{
                  printf("commmand preset player got\n");
                  char *temp = NULL;
                  temp = (char *)calloc(cmd->length-2+1, sizeof(char));
                  temp[0] = '0' + cmd->length-2+1;
                  for(int i=0; i<cmd->length-2; i++){
                      temp[i+1] = '0' + cmd->params[i+2];
                  }
                  init_reset(g, temp);
                  break;
              }
              default:{
                  printf("command preset got but no subcommand\n");
                  showMessage("preset followed by a unknow .\n");
                  break;
              }
          }
          break;
      }
      default:
          printf("what command did you input?\n");
          showMessage("command not in command set. some thing must be wrong.\n");
          break;
  }
  return 0;
}
