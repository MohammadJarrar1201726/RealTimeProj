#include "header.h"
#include "constants.h"
#include "player.h"
#include "gamefuncs.h"

struct PLAYER me;

int main(int argc, char* argv[]){

    // check arguments
    if(argc != 3){
        perror("USAGE: Not Enough Arguments for Player Process\n");
        exit(14);
    }


    // fill values
    me.teamnum = atoi(argv[1]);
    me.number = atoi(argv[2]);
    me.energy = get_energy_level(getpid());

    printf("[TEAM PLAYER NOTIFICATION]\nHello, I am Player(%d) in Team No.[%d] with Energy= %d\n", me.number, me.teamnum, me.energy);
    fflush(stdout);

   return(0);

}
