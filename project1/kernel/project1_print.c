#include <linux/linkage.h>
#include <linux/kernel.h>

asmlinkage void sys_project1_print(int pid, long start_time, long end_time){
    printk("[Project1] %d %ld.%09ld %ld.%09ld\n", pid, start_time/1000000000, start_time%1000000000, end_time/1000000000, end_time%1000000000);
    return;
}
