#include <stdio.h>
#include <crypt.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

static char *second;
static int count = 0;

static void interrupt_handler(int sig){
	crypt(second, "xx");
       	count++;	
}


int main(int argc, char * argv[]) {
	char * first;
	char * cs;
	int call, mismatch;
	struct sigaction control;

	if(argc != 3) {
		fprintf(stderr, "Usage: %s <first> <second>\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	first = argv[1];
	second = argv[2];

	cs = strdup(crypt(first, "xx"));
	printf("%s\n", cs); 


	sigemptyset(&control.sa_mask);
	//sigaddset(&control.sa_mask, SIGTERM);
	control.sa_flags = 0;
	control.sa_handler = interrupt_handler;

	if(sigaction(SIGINT, &control, NULL) == -1) {
		perror("sigaction");
		return EXIT_FAILURE;
	}

	
	for(call = 1, mismatch = 0; ; call++) {
		if(strcmp(crypt(first,"xx"), cs) != 0) {
			mismatch++;
			printf("Mismatch on call %d (mismatch=%d handled=%d)\n", call, mismatch, count);
		}
	}

	return EXIT_SUCCESS;
}
