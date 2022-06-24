// Header files begins //////////////////////////////////////////////////////////////////
#include <linux/init.h>   // Required header for initialization and clean up funtionalities
#include <linux/module.h> // This header contain the necessary stuff for the module
#include <linux/kernel.h>
#include "am.h"

// Header files ends //////////////////////////////////////////////////////////////////

MODULE_LICENSE("GPL");                     // tells that module bears free module
MODULE_AUTHOR("madhusudhan");              // Author name
MODULE_DESCRIPTION("kernal symbol table"); // Description about the module
MODULE_ALIAS("madhu");                     // Another name of the module

int my_add(int a, int b)
{
    return (a + b);
}
/* this is add func that we are going to export as symbol
 */
EXPORT_SYMBOL_GPL(my_add); // COMMAND TO EXPORT THE SYMBOL

static int __init hello_init(void)
{
    printk(KERN_ALERT "\n exporting the symbol to kernal symbol table\n"); // KERN_ALERT is the priority message : Decides the seriousness of message
                                                                           // printk(KERN_ALERT "\nThe value of charvar is %s\n", charvar);
    // printk(KERN_ALERT "\nThe value of a intvar %d\n", intvar);

    return 0; // return 0 for sucessfull compilation
}

// To removes module from the kernel

static void __exit hello_exit(void)
{
    printk("\n bye \n");
}

module_init(hello_init); // Module Initialization
module_exit(hello_exit); // Module De-Initialization
