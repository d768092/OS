#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#include <unistd.h>
#include <sys/types.h>
#include "process.h"
#ifndef SCHED_FIFO
#define SCHED_FIFO 1
#endif

void setcore(pid_t pid, int corenum){
	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(corenum, &mask);
	sched_setaffinity(pid, sizeof(mask), &mask);
	return;
}

void stop(pid_t pid){
	struct sched_param param;
	param.sched_priority = 1;
	sched_setscheduler(pid, SCHED_FIFO, &param);  //for running very low priority background jobs
	return;
}

void activate(pid_t pid){
	struct sched_param param;
	param.sched_priority = 99;
	sched_setscheduler(pid, SCHED_FIFO, &param);  //higher priority than others
	return;
}

pid_t new_process(process p){
	pid_t pid=fork();
	if(pid<0){
		perror("fork");
		return -1;
	}
	if(pid==0){
		for(int t=0;t<p.exec_time;t++){ volatile unsigned long i; for(i=0;i<1000000UL;i++); }
		exit(0); 
	}
	if(pid>0){
		setcore(pid, 1);
		return pid;
	}
}
