#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/unistd.h>
#include <linux/sched.h>
#include <linux/ktime.h>
#include <linux/timekeeping.h>
#include <linux/gfp.h>
#include <linux/mm_types.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>


#define PAGE_SIZE 4096

struct mystruct {
    unsigned int arr[8];
};

int init_module(void) {
    struct mystruct m;
    int temp1 = PAGE_SIZE/sizeof(m);
    printk(KERN_INFO "Part 2:");
    printk(KERN_INFO "Page size is: %d. \n", PAGE_SIZE);
    printk(KERN_INFO "Size of struct is: %d. \n", sizeof(m));
    printk(KERN_INFO "Number of instances is: %d. \n", temp1);
    return 0;
}

void cleanup_module(void) {
    printk(KERN_INFO "End of Part 2\n");
}