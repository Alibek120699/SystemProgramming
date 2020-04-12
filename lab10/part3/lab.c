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

MODULE_LICENSE("GPL");
#define PAGE_SIZE 4096

struct mystruct {
   unsigned int arr[8];
};

// static int param1 = 1000;
// static int param2 = 2000;
static int param3 = 4000;

// module_param(param1, int, 0660);
// module_param(param2, int, 0660);
module_param(param3, int, 0660);

struct page* mypages;

void pageAllocation(int temp1) {
    struct timespec t1, t2;
    int temp2 = param3/temp1 + 1;
    int pow = 0;

    if(temp2 == 8) {
        pow = 3;
    } else if(temp2 == 16) {
        pow = 4;
    } else if(temp2 == 32) {
        pow = 5;
    }

    printk(KERN_INFO "Part3: 2^%d=%d pages will bee allocated.", pow, temp2);
    getnstimeofday(&t1);

    mypages = alloc_pages(GFP_KERNEL, pow);
    __free_pages(mypages, pow);

    getnstimeofday(&t2);
    printk(KERN_INFO "Part3: Time when we started: %lu. \n", t1.tv_nsec);
    printk(KERN_INFO "Part3: Time when we finished: %lu. \n", t2.tv_nsec);
    printk(KERN_INFO "Part3: How much did it take: %lu. \n", t2.tv_nsec - t1.tv_nsec);
}


int init_module(void) {
    printk(KERN_INFO "Part3: Page Allocation.\n");
    printk(KERN_INFO "Part3: My module param: %d \n.", param3);
    struct mystruct m;
    int temp1 = PAGE_SIZE/sizeof(m);
    printk(KERN_INFO "Part3: Page size is: %d. \n", PAGE_SIZE);
    printk(KERN_INFO "Part3: Size of struct is: %d. \n", (int)sizeof(m));
    printk(KERN_INFO "Part3: Number of instances is: %d. \n", (int)temp1);
    pageAllocation(temp1);
    return 0;
}

void cleanup_module(void) {
   printk(KERN_INFO "Part3: End of Part 3\n");
}