#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/types.h>

typedef struct {
    char name[32];
    int ready_time;
    int exec_time;
	long start_time;
    pid_t pid;
}process;

void setcore(pid_t pid, int corenum);
pid_t new_process(process p);
void stop(pid_t pid);
void activate(pid_t pid);
