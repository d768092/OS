#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include "process.h"
#define RR_MAX 500

int main()
{
	setcore(0, 0);
	activate(0);
	char s[20];
	scanf("%s", s);
	int n;
	scanf("%d", &n);
	process *all=(process *)malloc(sizeof(process)*n);
	for(int i=0;i<n;i++) scanf("%s %d %d", all[i].name, &all[i].ready_time, &all[i].exec_time);
	for(int i=0;i<n;i++) all[i].pid=-1;
	int time=0;  //current time
	int now=-1;  //current running process
	int cnt=0;   //finished processes
	int last_rr=0;
	while(1){
		if(now!=-1&&all[now].exec_time==0){
        		waitpid(all[now].pid, NULL, 0);
			long end_time=syscall(333);
			syscall(334, all[now].pid, all[now].start_time, end_time);
        		printf("%s %d\n", all[now].name, all[now].pid);
			fflush(stdout);
			cnt++;
			now=-1;
			if(cnt==n) break;
		}
		for(int i=0;i<n;i++){
			if(all[i].ready_time==time){
				all[i].pid=new_process(all[i]);
				stop(all[i].pid);
				all[i].start_time=syscall(333);
			}
		}
		int next=-1;
		if(strcmp(s, "FIFO")==0){
			if(now==-1){
				for(int i=0;i<n;i++){
					if(all[i].pid==-1||all[i].exec_time==0) continue;
					if(next==-1||all[i].ready_time<all[next].ready_time) next=i;
				}
			}
			else next=now;
		}
		else if(strcmp(s, "PSJF")==0){
			for(int i=0;i<n;i++){
				if(all[i].pid==-1||all[i].exec_time==0) continue;
				if(next==-1||all[i].exec_time<all[next].exec_time) next=i;
			}
		}
		else if(strcmp(s, "RR")==0){
			if(now==-1||time-last_rr==RR_MAX){
				if(now!=-1) all[now].ready_time=time;
				for(int i=0;i<n;i++){
					if(all[i].pid==-1||all[i].exec_time==0) continue;
					if(next==-1||all[i].ready_time<all[next].ready_time){
						next=i;
						last_rr=time;
					}
				}
			}
			else next=now;
		}
		else if(strcmp(s, "SJF")==0){
			if(now==-1){
				for(int i=0;i<n;i++){
					if(all[i].pid==-1||all[i].exec_time==0) continue;
					if(next==-1||all[i].exec_time<all[next].exec_time) next=i;
				}
			}
		}
		else{
			perror("unknown policy");
			exit(0);
		}
		if(next!=-1&&next!=now){
			activate(all[next].pid);
			if(now!=-1) stop(all[now].pid);
			now=next;
		}
		volatile unsigned long i; for(i=0;i<1000000UL;i++);

		if(now!=-1) all[now].exec_time--;
		time++;
	}
	return 0;
}
