#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>


//TODO MAKE SIG HANDLER FUNCTION TO HANDLE SIGNALS
void sigHandler (int);

int main() {
	pid_t ppid, cpid;

	//GRAB PARENT PROCESS ID
	ppid = getpid();
	//printf("\nparent process: %d\n", ppid);
	//printf("\nsigusr1: %d | sigusr2: %d | sigint is: %d\n", SIGUSR1, SIGUSR2, SIGINT);
	
	//CREATE SIG HANDLER.
	signal(SIGUSR1, sigHandler);
	signal(SIGUSR2, sigHandler);
	signal(SIGINT,  sigHandler);

	//TEST OUT THE KILL FUNCTION.
	/*
	kill(getpid(),SIGUSR1);
	kill(getpid(),SIGUSR2);
	kill(getpid(),SIGINT);
	*/

	//FORK CHILD PROCESS
	cpid = fork();	

	//If parent
	if(cpid){
		printf("spawned child PID# %d\n", cpid);
		while(1){
			printf("\nwaiting...");
			pause();
		}
	}

	//If child
	if(!cpid){
		fclose(stdout);
		while(1){
			int sleep_time = rand() % 4 + 1;		
			int op         = rand() % 2;

			sleep(sleep_time);
			switch(op){
				case 0:			
					kill(ppid,SIGUSR1);
					break;
				case 1:
					kill(ppid,SIGUSR2);
					break;
			}
		}
	} 
	return 0;
}

void sigHandler(int sigNum){
	switch(sigNum){
		case SIGUSR1:
			printf(" recieved a SIGUSR1.\n");
			break;
		case SIGUSR2:
			printf(" received a SIGUSR2.\n");
			break;
		case SIGINT:
			printf(" ^C received.\n");
			printf("Thats it, I'm shutting you down...\n");
			exit(0);
			break;
	}	
}
