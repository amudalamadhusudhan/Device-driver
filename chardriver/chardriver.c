/* Hello World Program */

// Header files begins //////////////////////////////////////////////////////////////////
#include <linux/init.h>   // Required header for initialization and clean up funtionalities
#include <linux/module.h> // This header contain the necessary stuff for the module
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/kd.h>
#include <linux/types.h>
// Header files ends //////////////////////////////////////////////////////////////////

MODULE_LICENSE("GPL");        // tells that module bears free module
MODULE_AUTHOR("madhusudhan"); // Author name
MODULE_DESCRIPTION("module"); // Description about the module
MODULE_ALIAS("madhu");        // Another name of the module

dev_t dev = MKDEV(333, 0); // major number minor static allocation
// To initialize the module and load into kernel

static int __init driverI(void)
{
    register_chrdev_region(dev, 1, "simple char driver");
    printk(KERN_INFO "\n major =%d minor=%d\n", MAJOR(dev), MINOR(dev));
    printk(KERN_ALERT "char driver inserted sussfuly\n");
    return 0; // return 0 for sucessfull compilation
}

// To removes module from the kernel

static void __exit driverE(void)
{
    unregister_chrdev_region(dev, 1);
    printk(KERN_ALERT "\n char driver removed successfully\n");
}

module_init(driverI); // Module Initialization
module_exit(driverE); // Module De-Initialization
