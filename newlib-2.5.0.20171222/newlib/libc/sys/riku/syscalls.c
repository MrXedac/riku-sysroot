/* note these headers are all provided by newlib - you don't need to provide them */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdint.h>

#undef errno
extern int errno;

#define SYSCALL1(ret, id, arg1) __asm volatile("MOV %1, %%RAX; MOV %2, %%RBX; SYSCALL; MOV %%RAX, %0" : "=r"(ret) : "r"(id), "r"(arg1) : "rax", "rbx")
#define SYSCALL2(ret, id, arg1, arg2) __asm volatile("MOV %1, %%RAX; MOV %2, %%RBX; MOV %3, %%RDX; SYSCALL; MOV %%RAX, %0" : "=r"(ret) : "r"(id), "r"(arg1), "r"(arg2) : "rax", "rbx", "rdx")
#define SYSCALL3(ret, id, arg1, arg2, arg3) __asm volatile("MOV %1, %%RAX; MOV %2, %%RBX; MOV %3, %%RDX; MOV %4, %%RSI; SYSCALL; MOV %%RAX, %0" : "=r"(ret) : "r"(id), "r"(arg1), "r"(arg2), "r"(arg3) :"rax", "rbx", "rdx", "rsi")

void _exit()
{
	long ret;
	SYSCALL1(ret, (long)0xC, (long)0);
}

int close(int file)
{
	uint64_t ret;
	SYSCALL1(ret, (uint64_t)0x3, (uint64_t)file);
	return ret;
}

char *__env[1] = { 0 };
char **environ = __env; /* pointer to array of char * strings that define the current environment variables */

int execve(char *name, char **argv, char **env)
{
	uint64_t ret;
	SYSCALL3(ret, (uint64_t)0xB, (uint64_t)name, (uint64_t)argv, (uint64_t)env);
	return ret;
}

int fork()
{
	uint64_t ret;
	SYSCALL1(ret, (uint64_t)0xA, (uint64_t)0x0);
	return ret;
}

int fstat(int file, struct stat *st)
{
	st->st_mode = S_IFCHR;
	return 0;
}

int getpid()
{
	uint64_t ret;
	SYSCALL1(ret, (uint64_t)0x8, (uint64_t)0x0);
	return ret;
}

int isatty(int file)
{
	return 1;
}

int kill(int pid, int sig)
{
	errno = EINVAL;
	return -1;
}

int link(char *old, char *new)
{
	errno = EMLINK;
	return -1;
}

int lseek(int file, int ptr, int dir)
{
	return 0;
}

int open(const char *name, int flags, ...)
{
	uint64_t ret;
	SYSCALL2(ret, (uint64_t)0x2, name, (uint64_t)flags);
	return ret;
}

int read(int file, char *ptr, int len)
{
	uint64_t ret;
	SYSCALL3(ret, (uint64_t)0x4, (uint64_t)file, ptr, (uint64_t)len);
	return (int)ret;
}

caddr_t sbrk(int incr)
{
	uint64_t ret;
	SYSCALL1(ret, (uint64_t)0x10, (long)0x0);
	return (caddr_t)ret;
}

int stat(const char *file, struct stat *st)
{
	st->st_mode = S_IFCHR;
	return 0;
}

clock_t times(struct tms *buf)
{
	return -1;
}

int unlink(char *name)
{
	errno = ENOENT;
	return -1;
}

int wait(int *status)
{
	errno = ECHILD;
	return -1;
}

int waitpid(int pid, int *status)
{
	uint64_t ret;
	SYSCALL1(ret, (uint64_t)0xD, (uint64_t)pid);
	return ret;
}

int write(int file, char *ptr, int len)
{
	uint64_t ret;
	SYSCALL3(ret, (uint64_t)0x5, (uint64_t)file, ptr, (uint64_t)len);
	return (int)ret;
}

int gettimeofday(struct timeval *p, void *z)
{
	return -1;
}
