#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <execinfo.h>

#define FILE_PERMS ( S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH )
#define OPEN_FLAGS ( O_WRONLY | O_APPEND | O_CREAT )

int magic_trace(char *filename, char *file, char *function, int line, char *format, ...)
{
	static char loggingtime[0x5f];
	time_t t;
	time(&t);
	strftime(loggingtime, 0x5f, "%Y%m%d%H%M%S", localtime(&t));

	static char header[0x100];
	if (file != NULL && function != NULL && line != -1)
		snprintf(header, sizeof(header), "[%s %10s(%30s):%04d]", loggingtime, file, function, line);
	else
		snprintf(header, sizeof(header), "[%s]", loggingtime);

	static char message[0x400];
	va_list arglist;
	va_start(arglist, format);

	vsnprintf(message, sizeof(message), format, arglist);

	static char buffer[0x500];
	ssize_t num = snprintf(buffer, sizeof(buffer), "%s : %s\n", header, message);
	if (num < 0) return -1;

	int fd = open(filename, OPEN_FLAGS, FILE_PERMS);
	while (((num = write(fd, buffer, (size_t)num)) == -1) && (errno == EINTR));
	close(fd);
	return (int)num;
}

int stack_trace(char *filename)
{
	int fd = open(filename, OPEN_FLAGS, FILE_PERMS);

	void *frames[0xff];

	size_t size = backtrace (frames, 0xff);
	backtrace_symbols_fd(frames, size, fd);

	return close(fd);
}
