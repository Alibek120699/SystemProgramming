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

struct kmem_cache *km;

void kmemCacheAlloc(int size) {
    struct timespec t1, t2;
    km = kmem_cache_create("kmemCacheAllocation", size, 0, 
                        SLAB_HWCACHE_ALIGN|SLAB_PANIC|SLAB_POISON|SLAB_RED_ZONE, 
                        NULL);
    getnstimeofday(&t1);
    int i;
    char *buf;
    for(i = 0; i < param3; i++) {
        buf = kmem_cache_alloc(km, GFP_KERNEL);
        kmem_cache_free(km, buf);
    }
    getnstimeofday(&t2);
    printk(KERN_INFO "Part5: Time when we started: %lu. \n", t1.tv_nsec);
    printk(KERN_INFO "Part5: Time when we finished: %lu. \n", t2.tv_nsec);
    printk(KERN_INFO "Part5: How much did it take: %lu. \n", t2.tv_nsec - t1.tv_nsec);
}


int init_module(void) {
    printk(KERN_INFO "Part5: KmemCacheAllocation.\n");
    printk(KERN_INFO "Part5: My module param: %d \n.", param3);
    struct mystruct m;
    int temp1 = PAGE_SIZE/sizeof(m);
    printk(KERN_INFO "Part5: Page size is: %d. \n", PAGE_SIZE);
    printk(KERN_INFO "Part5: Size of struct is: %d. \n", (int)sizeof(m));
    printk(KERN_INFO "Part5: Number of instances is: %d. \n", (int)temp1);
    kmemCacheAlloc(sizeof(m));
    return 0;
}

void cleanup_module(void) {
   printk(KERN_INFO "Part5: End of Part 5\n");
   kmem_cache_destroy(km);
}