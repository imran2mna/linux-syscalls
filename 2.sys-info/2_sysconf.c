#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
	printf("Max. length of hostname \t: %ld\n", sysconf(_SC_HOST_NAME_MAX));
	printf("Max. child procs\t\t: %ld\n", sysconf(_SC_CHILD_MAX));
	printf("Max. opened files\t\t: %ld\n", sysconf(_SC_OPEN_MAX));
	printf("Max. no of arguments\t\t: %ld\n", sysconf(_SC_ARG_MAX));
	printf("No. processors configed\t\t: %ld\n", sysconf(_SC_NPROCESSORS_CONF));
	return EXIT_SUCCESS;
}
