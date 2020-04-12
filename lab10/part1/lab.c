#include <linux/module.h>
#include <linux/moduleparam.h>

static int param = 2000;
module_param(param, int, 0660);

int init_module(void){
    printk(KERN_INFO "Part 1:\n");
    printk(KERN_INFO "My module param: .%d\n", param);
}

void cleanup_module(void){
    printk("End of Part 1");
}
