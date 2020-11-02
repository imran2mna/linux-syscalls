/* This code to differentiate the real user-id and effective user-id.
 * Try to run this on different execution stages.
 * eg:- sudo <executable>
 * */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>


int main(void){
	// below id will be set on later
	int disguised_id = 121;

	/*
	 * The difference can be oberserved through 
	 * chown root:root <executable>
	 * chmod u+s <executable>
	 * */

	printf("Real user id \t: %d\n", getuid()); // user id of calling process
	printf("Eff. user id \t: %d\n", geteuid()); // effective id of process 


	//if(setuid(disguised_id) == -1) perror("setuid"); 
	if(seteuid(disguised_id) == -1) perror("seteuid");
	
	printf("Real user id \t: %d\n", getuid());
	printf("Eff. user id \t: %d\n", geteuid());

	if(setuid(0) == -1) perror("setuid");
	if(seteuid(0) == -1) perror("seteuid");
	
	printf("Real user id \t: %d\n", getuid());
	printf("Eff. user id \t: %d\n", geteuid());

	/*
	 * Read documentation about 'capabilities' man page,
	 * which provides great understanding. 
	 * CAP_SETUID
	 * */


	return EXIT_SUCCESS;
}
