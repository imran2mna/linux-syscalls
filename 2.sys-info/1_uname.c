//#define _GNU_SOURCE

#include <stdio.h>
#include <sys/utsname.h>
#include <stdlib.h>

int main(void) {
	struct utsname sys_info;

	if(uname(&sys_info) == -1) {
		perror("uname");
		return EXIT_FAILURE;
	}

	printf("Host name\t: %s\n", sys_info.nodename);
	printf("OS \t\t: %s\n", sys_info.sysname);
	printf("Kernel \t\t: %s\n", sys_info.release);
	printf("Version\t\t: %s\n", sys_info.version);
	printf("Architecture \t: %s\n", sys_info.machine);

	//printf("Domain\t\t: %s\n", sys_info.domainname);

	return EXIT_SUCCESS;
}
