#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include "process.h"

pid_t new_process(process p){
    pid_t pid=fork();
    if(pid<0){ perror("fork"); return -1;}
    if(pid==0){
        syscall(getntimesofday);  //start time
        for(int t=0;t<p.exec_time){ volatile unsigned long i; for(i=0;i<1000000UL;i++); }
        syscall(getntimesofday);  //end time

        syscall(printk);  //print to dmseg
        exit(0); 
    }
    if(pid>0) return pid;
}
void stop(process p){
    struct sched_param param;
    param.sched_priority = 0;
    sched_setscheduler(p.pid, SCHED_IDLE, &param);  //for running very low priority background jobs
    return;
}
void activate(process p){
    struct sched_param param;
    param.sched_priority = 0;
    sched_setscheduler(p.pid, SCHED_OTHER, &param);  //higher priority than others
    return;
}