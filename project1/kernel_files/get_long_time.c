#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/timer.h>

asmlinkage long sys_get_long_time(void){
    struct timespec t;
    getnstimeofday(&t);
    return t.tv_sec*1000000000+t.tv_nsec;
}
