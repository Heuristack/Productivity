 /**
 * TITLE: Print st_dev and st_rdev values
 * AUTHOR: LiYing
 * DATE: 2010-6-10 15:45:23
 * NOTE:
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

int
main(int argc, char *argv[]){

    int         i;
    struct stat buf;

    for (i = 1; i < argc; i++) {
        printf("%s: ", argv[i]);
        if (stat(argv[i], &buf) < 0) {
            fprintf(stderr, "stat error\n");
            continue;
         }

         printf("dev = %d/%d", major(buf.st_dev), minor(buf.st_dev));
         if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode)) {
             printf(" (%s) rdev = %d/%d",
                     (S_ISCHR(buf.st_mode)) ? "character" : "block",
                     major(buf.st_rdev), minor(buf.st_rdev));

         }
         printf("\n");
    }
    exit(0);
}/*main*/
