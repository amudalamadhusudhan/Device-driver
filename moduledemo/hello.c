/* Hello World Program */

// Header files begins //////////////////////////////////////////////////////////////////
#include <linux/init.h>   // Required header for initialization and clean up funtionalities
#include <linux/module.h> // This header contain the necessary stuff for the module
#include <linux/kernel.h>
// Header files ends //////////////////////////////////////////////////////////////////

MODULE_LICENSE("GPL");        // tells that module bears free module
MODULE_AUTHOR("madhusudhan"); // Author name
MODULE_DESCRIPTION("module"); // Description about the module
MODULE_ALIAS("madhu");        // Another name of the module

// To initialize the module and load into kernel

static int hello_init(void)
{
    printk(KERN_ALERT "\n Hello World new module\n");

    return 0; // return 0 for sucessfull compilation
}

// To removes module from the kernel

static void hello_exit(void)
{
    printk("\n bye module \n");
}

module_init(hello_init); // Module Initialization
module_exit(hello_exit); // Module De-Initialization
