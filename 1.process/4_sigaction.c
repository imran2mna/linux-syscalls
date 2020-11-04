#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>


static void handler(int sig, siginfo_t *info, void *ucontext) {
	printf("Received from = %d, user = %d\n", info->si_pid, info->si_uid);
}

int main(void) {
	printf("pid : %d\n", getpid());
	struct sigaction control;
	
	control.sa_flags = SA_SIGINFO;
	control.sa_sigaction = &handler;
	
	if(sigaction(SIGTERM, &control, NULL) == -1) {
		perror("sigaction");
		return EXIT_FAILURE;
	}


	while(1) sleep(1);

	return EXIT_SUCCESS;
}
