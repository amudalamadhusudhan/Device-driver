// Header files begins //////////////////////////////////////////////////////////////////
#include <linux/init.h>   // Required header for initialization and clean up funtionalities
#include <linux/module.h> // This header contain the necessary stuff for the module
#include <linux/kernel.h>
#include "am.h"
//#include "myadd.h"
// Header files ends //////////////////////////////////////////////////////////////////

MODULE_LICENSE("GPL");                     // tells that module bears free module
MODULE_AUTHOR("madhusudhan");              // Author name
MODULE_DESCRIPTION("kernal symbol table"); // Description about the module
MODULE_ALIAS("madhu");                     // Another name of the module
// static int a = 10, result, b = 23;
static int __init hello_init(void)
{
    printk(KERN_ALERT "\n kernal symbol exported\n");
    // result = my_add(a, b);
    //  KERN_ALERT is the priority message : Decides the seriousness of message
    printk(KERN_ALERT "\n the result my_add is %d\n", my_add(10, 20));
    // printk(KERN_ALERT "\nThe value of a intvar %d\n", intvar);

    return 0; // return 0 for sucessfull compilation
}

// To removes module from the kernel

static void __exit hello_exit(void)
{
    printk("\n bye kst \n");
}

module_init(hello_init); // Module Initialization
module_exit(hello_exit); // Module De-Initialization
