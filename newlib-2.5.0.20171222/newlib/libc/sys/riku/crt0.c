#include <fcntl.h>

extern void exit(int code);
extern int main (int, char**);
extern void _init_signal();

void _start() {
    long argc;
    char** argv;

    __asm volatile("MOVQ %%R12, %0; \
		    MOVQ %%R13, %1;"
		    : "=r" (argc), "=r" (argv));

    _init_signal();
    int ex = main(argc, argv);
    exit(ex);
}
