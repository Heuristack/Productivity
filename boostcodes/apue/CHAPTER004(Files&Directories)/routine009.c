/**
 * TITLE: Recursively descend a directory hierarchy, counting file types
 * AUTHOR: LiYing
 * DATE: 2010-6-10 16:09:11
 * NOTE:
 */

#include<stdio.h>
#include<dirent.h>
#include<limits.h>
#include<fcntl.h>
#include<sys/stat.h>

typedef int Myfunc(const char *, const struct stat *, int);

static Myfunc	myfunc;
static int		myftw(char *, Myfunc *);
static int 		dopath(Myfunc *);

static long nreg, ndir, nblk, nchr, nfifo, nsock, nslink, ntot;

int
main(int argc, char *argv[]){
   	int ret;

    if (argc != 2) {
        fprintf(stderr, "usage: ftw <starting-pathname>\n");
        exit(-1);
	}/*illegal argument*/

    ret = myftw(argv[1], myfunc);        /* does it all */

    ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
    if (ntot == 0)
        ntot = 1;       /* avoid divide by 0; print 0 for all counts */
    printf("regular files  = %7ld, %5.2f %%\n", nreg,
      nreg*100.0/ntot);
    printf("directories    = %7ld, %5.2f %%\n", ndir,
      ndir*100.0/ntot);
    printf("block special  = %7ld, %5.2f %%\n", nblk,
      nblk*100.0/ntot);
    printf("char special   = %7ld, %5.2f %%\n", nchr,
      nchr*100.0/ntot);
    printf("FIFOs          = %7ld, %5.2f %%\n", nfifo,
      nfifo*100.0/ntot);
    printf("symbolic links = %7ld, %5.2f %%\n", nslink,
      nslink*100.0/ntot);
    printf("sockets        = %7ld, %5.2f %%\n", nsock,
      nsock*100.0/ntot);

    exit(ret);

}/*main*/

#define FTW_F	1		/* file other than directory */
#define FTW_D	2		/* directory */
#define FTW_DNR	3		/* directory that can't be read */
#define FTW_NS	4		/* file that we can't stat */

static char fullpath[1024];		/*contains full pathname for every file*/

static int
myftw(char *pathname, Myfunc *func){
	strncpy(fullpath, pathname, sizeof(fullpath));
	fullpath[1024-1] = '\0';
	return (dopath(func));
}/*myftw*/

static int
dopath(Myfunc *func){
	struct stat statbuf;
	struct dirent *dirp;
	DIR *dp;
	int ret;
	char *ptr;

	if (lstat(fullpath, &statbuf) < 0)				/*stat error*/
		return (func(fullpath, &statbuf, FTW_NS));
	if (S_ISDIR(statbuf.st_mode) == 0)				/*not a directory*/
		return (func(fullpath, &statbuf, FTW_F));

	if ((ret = func(fullpath, &statbuf, FTW_D)) != 0)
		return (ret);

	ptr = fullpath + strlen(fullpath);				/* point to end of fullpath */
	*ptr++ = '/';
	*ptr = '\0';

	if ((dp = opendir(fullpath)) == NULL)			/* can't read directory */
		return (func(fullpath, &statbuf, FTW_DNR));

	while ((dirp = readdir(dp)) != NULL){
		if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
			continue;
		strcpy(ptr, dirp->d_name);

		if ((ret = dopath(func)) != 0)
			break;
	}/*recursive-traverse*/

	ptr[-1] = '\0';    /* erase everything from slash onwards */

	if (closedir(dp) < 0) {
		fprintf(stderr, "closedir failed\n");
		exit(-1);
	}/*closedir-failed*/
	return (ret);
}/*dopath*/

static int
myfunc(const char *pathname, const struct stat *statptr, int type){
	switch(type){
		case FTW_F:
			switch(statptr->st_mode & S_IFMT) {
				case S_IFREG:
					nreg++;
					break;
				case S_IFBLK:
					nblk++;
					break;
				case S_IFCHR:
					nchr++;
					break;
				case S_IFIFO:
					nfifo++;
					break;
				case S_IFLNK:
					nslink++;
					break;
				case S_IFSOCK:
					nsock++;
					break;
				case S_IFDIR:
					fprintf(stderr, "for S_IFDIR for %s", pathname);
					abort();
					break;
			}/**/
			break;

		case FTW_D:
			ndir++;
			break;

		case FTW_DNR:
			fprintf(stderr, "can't read directory %s\n", pathname);
			break;

		case FTW_NS:
			fprintf(stderr, "stat error for %s\n", pathname);
			break;

		default:
			fprintf(stderr, "unknown type %d for pathname %s\n", type, pathname);
			abort();
	}/*switch*/
	return (0);
}/*myfunc*/

