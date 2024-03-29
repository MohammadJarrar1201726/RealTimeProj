#include "header.h"
#include "functions.h" 
#include "constants.h"
#include "gamefuncs.h"

// prototypes


int *teams;


// game parameters
int current_round = 1; 
int is_round_end = 0;

int main(){
    // assign values to GAME SETTINGS
    read_settings_file("settings.txt");
    ask_user_tofill_settings();
    display_settings_and_init();
    


    teams = malloc(sizeof(int) * NUMBER_OF_TEAMS);
    pid_t pid;

    printf("%d\n\n", NUMBER_OF_TEAMS);
    // create teams for the game 
    for(int i=0; i<NUMBER_OF_TEAMS; i++){
        if((pid=fork()) == -1){
            perror("FORK: No Enough Memory\n");
            exit(5); 
        } else if(pid == 0){
            // child process (team)

            char team_num[20], num_of_players[20];
            sprintf(team_num, "%d", (i+1)); 
            sprintf(num_of_players, "%d", NUMBER_OF_PLAYERS);
            execlp("./team", "team", team_num, num_of_players, NULL);

            // if no error, the team process will not execute this
            perror("EXEC: Can't Execute Team Functionality\n");
            exit(6);

        } else{
            // parent process (Owner of the game)

            teams[i] = pid; /* Save team pid */
            printf("[GAME NOTIFICATION]:\nTEAM NO.[%d] CREATED SUCCESSFULLY\n", (i+1));
        }
    }

    sleep(15); // wait until all children be created




    // Starting the game from the parent application
    printf("-------------------STARTING THE GAME--------------------------\n\n");


    // game signals (sensitive)
    if ( sigset(SIGALRM, end_round) == SIG_ERR ) {
        perror("Sigset can not set SIGALRM");
        exit(SIGINT);
    }

    if ( sigset(SIGUSR1, send_ball) == SIG_ERR){
        perror("SIGNAL: can not set SIGUSR1\n");
        exit(SIGUSR1);
    }

    if ( sigset(SIGUSR2, send_ball) == SIG_ERR){
        perror("SIGNAL: can not set SIGUSR1\n");
        exit(SIGUSR1);
    }





    while(1){
        // START ROUND
        is_round_end =0;
        alarm(ROUND_DURATION); // alarm to end the round
        printf("=========== ROUND [%d] Started ===========\n",current_round);
        
        // send the ball for each team
        for(int i=0; i<NUMBER_OF_TEAMS; i++){
            kill(teams[i], SIGUSR1); // send a ball for each team
        }

        // wait until the round end
        while(!is_round_end){
            pause();
        }

        // END ROUND
        if(current_round > NUMBER_OF_ROUNDS){
            // END GAME (exit)
            break;
        }
        
    }


    // sensitive to teams 

    sleep(20);
    return(0);

}



void end_round(int sig){
    // TODO:
    // send end signal for the teams

        // build fifo
        // write to fifo "send_info"






    // ask for full information 
    // recv full information and print it
    // increment number of rounds
    current_round += 1;
    is_round_end = 1;

}


void send_ball(int team_sig){
    if(team_sig == SIGUSR1){
        // send ball to team 1
        kill(teams[0], SIGUSR1);
    } else {
        // send ball to team 2
        kill(teams[1], SIGUSR1);
    }
}

