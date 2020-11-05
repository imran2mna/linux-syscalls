#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#define MASK_PERIOD 10

void sighandle(int sig){
	switch(sig) {
		case SIGINT:
			printf("Received SIGINT\n");
			break;
		case SIGTERM:
			printf("Received SIGTERM\n");
			break;
		case SIGHUP:
			printf("Received SIGHUP\n");
			exit(0);
			break;
	}
}

int main(void){
	sigset_t init_mask, act_mask;

	/* both SIGKILL and SIGSTOP can not be masked or handled by programmer
	 * defined handlers. Other signals can be handled in custom manner. 
	 */

	sigemptyset(&act_mask);
	sigaddset(&act_mask, SIGINT);
	sigaddset(&act_mask, SIGTERM);
	sigaddset(&act_mask, SIGHUP);

	if(signal(SIGINT, sighandle) == SIG_ERR || signal(SIGTERM, sighandle) == SIG_ERR || signal(SIGHUP, sighandle) == SIG_ERR) {
		perror("signal");
		return EXIT_FAILURE;
	}

	// apply new signal mask & preserve the previous mask for restoring.
	if(sigprocmask(SIG_BLOCK, &act_mask, &init_mask) == -1) {
		perror("sigprocmask");
		return EXIT_FAILURE;
	}  		

	printf("\033[0;32mInterrupts are masked for %d seconds.\033[0m\n", MASK_PERIOD);
	
	// during MASK_PERIOD interrupts are not caught
	sleep(MASK_PERIOD);


	// restoring initial signal mask
	if(sigprocmask(SIG_SETMASK, &init_mask, NULL) == -1) {
		perror("sigprocmask");
		return EXIT_FAILURE;
	}
	printf("\033[0;31mInterrupts enabled.\033[0m\n");	
	
	// self-joke :)
	kill(getpid(), SIGINT);  
	
	while(1) sleep(1);

	return EXIT_SUCCESS;
}
