#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <pwd.h>
#include <grp.h>


int main(int argc, char* argv[]){
	char* prg = argv[0];
	char* filePath = NULL;
	struct stat * info = NULL;

	if(argc != 2) {
		fprintf(stderr, "Usage: %s <path>\n", prg);
		exit(EXIT_FAILURE);
	}

/*
====
NOTE
====
Before passing the stat struct pointer into stat(), we need to initialize the struct.
Otherwise we need to provide memory location of the static area 'stat struct' variable
eg: 
..........
struct stat sb;
lstat(argv[1], &sb);
*/
	
	filePath = argv[1];
	info = (struct stat *) malloc(sizeof(struct stat));

	// lstat() detects the symbolic links, which can not be acheived through stat()
        if(lstat(filePath,info) == -1) {
		perror("stat");
		exit(EXIT_FAILURE);	
	}
	
	printf("File\t\t: %s\n", filePath);
	printf("Device\t\t: [%lx,%lx]\n", (long) major(info->st_dev),
		       	(long) minor(info->st_dev));


	struct passwd * user = getpwuid(info->st_uid);
	printf("Uid\t\t: %d\t(%s)\n", info->st_uid, (user!= NULL) ? user->pw_name:"Unknown");

	struct group * gid = getgrgid(info->st_gid);
	printf("Gid\t\t: %d\t(%s)\n", info->st_gid, (gid!=NULL) ? gid->gr_name: "Unknown");
	printf("Mode\t\t: %o\n", info->st_mode );
	
	printf("File Type\t: ");
	switch(info->st_mode & S_IFMT) {
		case S_IFBLK:  printf("block device\n");            break;
		case S_IFCHR:  printf("character device\n");        break; 
		case S_IFDIR:  printf("directory\n");               break;
		case S_IFIFO:  printf("FIFO pipe\n");               break;
		case S_IFLNK:  printf("symlink\n");                 break;
		case S_IFREG:  printf("regular file\n");            break;
		case S_IFSOCK: printf("socket\n");                  break;
	       	default:       printf("unknown?\n");                break;
	}

	printf("Hard Links\t: %ld\n", info->st_nlink);
        printf("Inode\t\t: %ld\n", info->st_ino);
	printf("Size\t\t: %lld\n", (long long) info->st_size);
	printf("Block Size\t: %ld\n", (long) info->st_blksize);
	printf("Blocks\t\t: %lld\n", (long long) info->st_blocks);
	
	printf("Last Access\t: %s", ctime(&info->st_atime));
	printf("Last Status\t: %s", ctime(&info->st_ctime));
	printf("Last Modify\t: %s", ctime(&info->st_mtime));
	
	if(info) { free(info); info = ((void *)0); }
}
