#include "header.h"
#include "constants.h"
#include "team.h"
#include "gamefuncs.h"

struct TEAM our_team;

int main(int argc, char* argv[]){

    // check arguments
    if(argc != 3){
        perror("USAGE: Not Enough Arguments for Team Process\n");
        exit(7);
    }

    // get arguments
    our_team.teamnumber = atoi(argv[1]);
    our_team.number_of_players = atoi(argv[2]);
    our_team.teamlead_energy = get_energy_level(getpid());
    our_team.num_of_balls = 0; // initial value 

    printf("[TEAM NOTIFICATION]\nHello, I am the Team Lead of Team No.[%d] with Energy = %d\n", our_team.teamnumber, our_team.teamlead_energy);
    fflush(stdout);

    // create players
    pid_t players[our_team.number_of_players];
    pid_t pid;

    for(int i=0; i<our_team.number_of_players; i++){
        if((pid=fork()) == -1){
            perror("FORK-PLAYER: No Enough Memory\n");
            exit(10);
        } else if(pid == 0){
            // child process - player

            char teamnum[20], playernum[20];
            sprintf(teamnum, "%d", our_team.teamnumber);
            sprintf(playernum, "%d", (i+1));
            
            execlp("./player", "player", teamnum, playernum, NULL);
            
            // if no error, this section will not be executed
            perror("EXEC-PLAYER: Can't Execute Player Process\n");
            exit(12);

        } else{
            // parent process - team
            players[i] = pid;
        }
    }

    // TEAM TODO:

    if(sigset(SIGUSR1, recv_ball) == SIG_ERR){
        perror("SIGNAL: Can't sigset to SIGUSR1\n");
        exit(30);
    }

    if(sigset(SIGUSR2, send_info) == SIG_ERR){
        perror("SIGNAL: Can't sigset to SIGUSR1\n");
        exit(35);
    }


    while(1){
        pause();
    }



   return(0);

}

void recv_ball(int ball_sig){
    our_team.num_of_balls += 1;
    printf("[TEAM %d]: A Ball Received from the parent\n\t[Total Balls = %d]\n", our_team.teamnumber, our_team.num_of_balls);
    fflush(stdout);
}


void send_info(int end_rd_sig){
    // TODO:

    // build fifo
    
    // write all information to the parent




}

