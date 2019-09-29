/*
  dump
*/

#include "dump.h"

bool debug_dump(GAME *g)
{
  FILE *fp = fopen(g->save_path,"w");
  if(fp==NULL) return false;

  int i,j;
  int bomb_num=0;
  int block_num=0;
  int bomb_locs[70];
  int block_locs[70];
  int level0[70], level0_l=0;
  int level1[70], level1_l=0;
  int level2[70], level2_l=0;
  int level3[70], level3_l=0;
  int rounds = g->rounds;

  for(i=0;i<MAP_SIZE;i++){
    LOCATION loc = g->map.local[i];
    if(loc.block==true) {
      block_locs[block_num]=i;
      block_num++;
    }
    if(loc.bomb==true) {
      bomb_locs[bomb_num]=i;
      bomb_num++;
    }
  }

  fprintf(fp,"bomb_locs:");
  for(i=0;i<bomb_num;i++){
    fprintf(fp,"%d",bomb_locs[i]);
    if(i!=bomb_num-1){
      fprintf(fp,",");
    }
  }
  fprintf(fp,"\n");

  fprintf(fp,"block_locs:");
  for(i=0;i<block_num;i++) {
    fprintf(fp,"%d",block_locs[i]);
    if(i!=block_num-1){
      fprintf(fp,",");
    }
  }
  fprintf(fp,"\n");
  
  fprintf(fp,"rounds:%d\n",g->rounds);

  for(i=0;i<g->player_num;i++){
    PLAYER player = g->players[i];
    fprintf(fp,"\n");
    fprintf(fp,"id:%d\n",player.id);
    fprintf(fp,"symbol:%c\n",player.name);
    fprintf(fp,"loc:%d\n",player.index);
    fprintf(fp,"points:%d\n",player.point);
    fprintf(fp,"fund:%d\n",player.money);
    fprintf(fp,"block:%d\n",player.gift[1]);
    fprintf(fp,"bomb:%d\n",player.gift[0]);
    fprintf(fp,"robot:%d\n",player.gift[2]);

    level0_l = level1_l = level2_l = level3_l = 0;
    for(j=0;j<player.house_num;j++){
      int index = player.house_index[j];
      switch(g->map.local[index].level){
        case 0:
        level0[level0_l] = index;
        level0_l++;
        break;
        case 1:
        level1[level1_l] = index;
        level1_l++;
        break;
        case 2:
        level2[level2_l] = index;
        level2_l++;
        break;
        case 3:
        level3[level3_l] = index;
        level3_l++;
        break;
        default:;
      }
    }
    
    fprintf(fp,"house_level_0:");
    for(j=0;j<level0_l;j++){
      fprintf(fp,"%d",level0[j]);
      if(j!=level0_l-1){
        fprintf(fp,",");
      }
    }
    fprintf(fp,"\n");

    fprintf(fp,"house_level_1:");
    for(j=0;j<level1_l;j++){
      fprintf(fp,"%d",level1[j]);
      if(j!=level1_l-1){
        fprintf(fp,",");
      }
    }
    fprintf(fp,"\n");

    fprintf(fp,"house_level_2:");
    for(j=0;j<level2_l;j++){
      fprintf(fp,"%d",level2[j]);
      if(j!=level2_l-1){
        fprintf(fp,",");
      }
    }
    fprintf(fp,"\n");

    fprintf(fp,"house_level_3:");
    for(j=0;j<level3_l;j++){
      fprintf(fp,"%d",level3[j]);
      if(j!=level3_l-1){
        fprintf(fp,",");
      }
    }
    fprintf(fp,"\n");

    fprintf(fp,"prison_cnt:%d\n",player.police_days);
    fprintf(fp,"bless_cnt:%d\n",player.bless_days);
    fprintf(fp,"hospital_cnt:%d\n",player.hospital_days);
	fprintf(fp,"stop_cnt:%d\n",player.magic_time);
    fprintf(fp,"is_bankrupt:%d\n",player.playerStatus);
  }

  fclose(fp);

  return true;
}

int save_archieve(GAME *g){
  FILE *fp = fopen(".arch", "wb");
  if(fp==NULL){
    printf("Error ==> fail to generate archieve file. please check your file system..");
    exit(0);
  }

  // fprintf(fp, "%d\n", g->player_less_num);
  // fprintf(fp, "%d\n", g->player_num);
  // fprintf(fp, "%d\n", g->playerIndex);
  // fprintf(fp, "%s\n", g->save_path);
  // fprintf(fp, "%d\n", g->rounds);
  /* save game struct finished */
    showSystemMessage("save to archieve success.");
  fwrite(g, sizeof(*g), 1, fp);
  fclose(fp);
  return 1;
}
