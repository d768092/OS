#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/types.h>

typedef struct {
    char name[32];
    int ready_time;
    int exec_time;
    pid_t pid;
}process;

pid_t new_process(process p);
void stop(process p);
void activate(process p);