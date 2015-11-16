/**
 * Subject: Resource Limits
 * Author: LiYing
 */
/**
 * FUNCTION PROTOTYPE
 * #include<sys/resource.h>
 * int getrlimit(int resource, struct rlimit *rlptr);
 * int setrlimit(int resource, const struct limit *rlptr);
 * Returns: zero if OK, non-zero on error
 */
/**
 * RESOURCE LIMIT
 * struct rlimit {
 *     rlim_t rlim_cur;		/*soft limit: current limit
 *     rlim_t rlim_max;		/*hard limit: maximum value for rlim_cur
 * };
 */
/**
 * RESOURCE-LIMIT CHANGING RULES
 * (a)a process can change soft limit < hard limit
 * (b)a process can change hard limit > soft limit
 * (c)only a superuser process can raise hard limit
 */
/**
 * RLIMIT_AS:	1.Total bytes of the process;2.Affects:sbrk && mmap;
 * RLIMIT_CORE:	1.Maximun size of a core file;2.Prevent creation of 'core' if 0;
 * RLIMIT_CPU:	1.Maximun amount of CPU time in seconds;2.SIGXCPU is sent to the process, if soft limit is extended;
 * RLIMIT_DATA:	1.The maximum size in bytes of the data segment: the sum of the initialized data, uninitialized data, and heap.
 * RLIMIT_FSIZE:1.The maximum size in bytes of a file that may be created;2.When the soft limit is exceeded, the process is sent the SIGXFSZ signal.
 * RLIMIT_LOCKS:1.The maximum number of file locks a process can hold
 * RLIMIT_MEMLOCK: 1.The maximum amount of memory in bytes that a process can lock into memory using mlock
 * RLIMIT_NOFILE:1.The maximum number of open files per process
 * RLIMIT_NPROC:1.The maximum number of child processes per real user ID
 * RLIMIT_RSS:	1.Maximum resident set size (RSS) in bytes
 * RLIMIT_SBSIZE:1.The maximum size in bytes of socket buffers that a user can consume at any given time
 * RLIMIT_STACK:1.Maxinum size in bytes of the stack;
 * RLIMIT_VMEM:	1.Synonym for RLIMIT_AS;
 * RLIM_INFINITY:infinite
 */
/**
 * INHERITANCE
 * 1.The calling process
 * 2.Inherited by all children
 */
/**
 * ISO C STRING CREATION OPERATOR #
 * #define print(string) printf(#string);
 * print(helloworld)
 * printf("helloworld");
 */
#include<stdio.h>
#include<sys/resource.h>

#define FMT "%10lld "
#define doit(name) pr_limit(#name, name)

static void pr_limit(char *name, int resource);

int main(int argc, char *argv[]){
#ifdef  RLIMIT_AS
    doit(RLIMIT_AS);
#endif
    doit(RLIMIT_CORE);
    doit(RLIMIT_CPU);
    doit(RLIMIT_DATA);
    doit(RLIMIT_FSIZE);
#ifdef  RLIMIT_LOCKS
    doit(RLIMIT_LOCKS);
#endif
#ifdef  RLIMIT_MEMLOCK
    doit(RLIMIT_MEMLOCK);
#endif
    doit(RLIMIT_NOFILE);
#ifdef  RLIMIT_NPROC
    doit(RLIMIT_NPROC);
#endif
#ifdef  RLIMIT_RSS
    doit(RLIMIT_RSS);
#endif
#ifdef  RLIMIT_SBSIZE
    doit(RLIMIT_SBSIZE);
#endif
    doit(RLIMIT_STACK);
#ifdef  RLIMIT_VMEM
    doit(RLIMIT_VMEM);
#endif
    exit(0);
}/*main*/

static void pr_limit(char *name, int resource){
	struct rlimit limit;
	if (getrlimit(resource, &limit) != 0)
		printf("error\n");
	printf("%-14s ", name);
	if (limit.rlim_cur == RLIM_INFINITY)
		printf("(infinite) ");
	else
		printf(FMT, limit.rlim_cur);
	if (limit.rlim_cur == RLIM_INFINITY)
		printf("(infinite)");
	else
		printf(FMT, limit.rlim_max);
	putchar('\n');
}/*pr_limit*/
