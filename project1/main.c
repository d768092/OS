#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "process.h"
#define RR_MAX 500

int main()
{
    char s[20];
    scanf("%s", s);
    int n;
    scanf("%d", &n);
    process *all=(process *)malloc(sizeof(process)*n);
    for(int i=0;i<n;i++) scanf("%s %d %d", all[i].name, all[i].ready_time, all[i].exec_time);
    int time=0;  //current time
    int now=-1;  //current running process
    int cnt=0;   //finished processes
    int last_rr=-1;
    while(1){
        if(now!=-1&&all[now].exec_time==0){
            waitpid(all[now].pid);
            printf("%s %d\n", all[now].name, all[now].pid);
            cnt++;
            now=-1;
            if(cnt==n) break;
        }
        for(int i=0;i<n;i++){
            if(all[i].ready_time==time){
                all[i].pid=new_process(all[i]);
                stop(all[i]);
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
        }
        else if(strcmp(s, "PSJF")==0){
            for(int i=0;i<n;i++){
                if(all[i].pid==-1||all[i].exec_time==0) continue;
                if(next==-1||all[i].exec_time<all[next].exec_time) next=i;
            }
        }
        else if(strcmp(s, "RR")==0){
            if(now==-1||time-last_rr==RR_MAX){
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
            stop(all[now]);
            activate(all[next]);
            all[now].ready_time=time;
            now=next;
        }
        volatile unsigned long i; for(i=0;i<1000000UL;i++);

        if(now!=-1) all[now].exec_time--;
        time++;
    }
    return 0;
}