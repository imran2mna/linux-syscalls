#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <shadow.h>
#include <crypt.h>

#define BUF_SIZE 64

void print(char * arg) {
	write(fileno(stdout), arg, strlen(arg));
}

int main(void){
	struct termios oflags, nflags;
	int len = -1;
	char * password = (char*) malloc(BUF_SIZE * sizeof(char));
	char * username = (char*) malloc(BUF_SIZE * sizeof(char));
	char * encrypted = NULL;
	struct passwd * pwd = NULL;
	struct spwd * spwd = NULL;


	printf("Enter username : ");
	fflush(stdout);
	if((len = read(fileno(stdin), username, BUF_SIZE)) < 0) {
		perror("read");
		return EXIT_FAILURE;
	}
	username[len - 1] = '\0';

	/*disable echo*/
	tcgetattr(fileno(stdin), &oflags);
	nflags = oflags;
	nflags.c_lflag &= ~ECHO;
	nflags.c_lflag |= ECHONL;
	if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
		perror("tcsetattr");
		return EXIT_FAILURE;
	}
	
	/* receive password*/
	print("password: ");
	if((len = read(fileno(stdin), password, BUF_SIZE)) < 0) {
		perror("read");
		return EXIT_FAILURE;
	}
	password[len - 1] = '\0';
	//fprintf(stdout, "you typed '%s'\n", password);

	/* restore terminal */
	if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
		perror("tcsetattr");
		return EXIT_FAILURE;
	}

	pwd = getpwnam(username);
	if(pwd == NULL) {
		return EXIT_FAILURE;
	}	

	spwd = getspnam(username);
	if(spwd == NULL) {
		return EXIT_FAILURE;
	}
	pwd->pw_passwd = spwd->sp_pwdp;
	encrypted = crypt(password, pwd->pw_passwd);
	char * p;
	for(p = password; *p != '\0'; p++) {
		*p = '\0';
	}

	if(strcmp(encrypted, pwd->pw_passwd) == 0) {
		printf("Authenticated.\n");
	} else {
		return EXIT_FAILURE;
	}

	if(setuid(pwd->pw_uid) == -1) {
		return EXIT_FAILURE;
	}

	if(seteuid(pwd->pw_uid) == -1) {
		return EXIT_FAILURE;
	}
	
	
	printf("Running as - %d, %d\n", getuid(), geteuid());


	if( close(fileno(stdin)) == -1 || close(fileno(stdout)) == -1 || close(fileno(stderr)) == -1) {
		perror("close");
		return EXIT_FAILURE;
	}

	return 0;
}
