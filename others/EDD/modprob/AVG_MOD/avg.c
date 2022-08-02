#include<linux/init.h>  // Required header fot the Initiallization and Cleanup Functionalities
#include<linux/module.h>  // this Header contains the necessary stuff for the module
#include<linux/moduleparam.h>  // This header allows the passing of parameter to the modules during insertion
#include"my_add.h"

MODULE_LICENSE("GPL");  // Macros that decide the license of the module
MODULE_AUTHOR("KAJOL");
MODULE_DESCRIPTION("Export symbol module");

static int one = 10;
static int two = 20;

// Initialization function for the program
static int __init add_init(void)
{
    printk(KERN_ALERT "Initialization of module\n");
    printk(KERN_ALERT "We are going to add \n");
    printk(KERN_ALERT "Result ADD : %d \n", my_add(one,two));
    
//    printk(KERN_ALERT "Average of two number : %d\n", (my_add(30,30))/2);

    return 0;

}

// cleanup function
static void __exit add_exit(void)
{
    printk(KERN_ALERT "exit from Module\n");
}

// MACROS that allow the user to override the names of the above mentioned functions with thier own choice....
module_init(add_init);  // for INITIALIZATION function
module_exit(add_exit);  // for CLEANUP function


