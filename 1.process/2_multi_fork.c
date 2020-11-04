#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

#define NO_PROCS 10

int main(void){
	int pid=getpid(), i=0;

	printf("\033[0;32mparent pid \t\t\t: %d, i=%d\033[0m\n", pid,i);

	// evaluating pid value prevents child process from forking inside it's address space.
	for(; (i < NO_PROCS) && (pid > 0) ; i++) {
		sleep(1);
		if((pid = fork()) == -1) {
			perror("fork");
			return EXIT_FAILURE;
		}
	}

	if(pid == 0) { 
		printf("child pid \t\t\t: %d, i=%d\n", getpid(),i);
	} else {
		wait(&pid);
		sleep(1);
		printf("\033[0;32mparent pid \t\t\t: %d, i=%d\033[0m\n", getpid(),i);
	}

	return EXIT_SUCCESS;
}
