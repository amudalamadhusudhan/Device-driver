// Header files begins //////////////////////////////////////////////////////////////////
#include <linux/init.h>   // Required header for initialization and clean up funtionalities
#include <linux/module.h> // This header contain the necessary stuff for the module
#include <linux/kernel.h>
// Header files ends //////////////////////////////////////////////////////////////////

MODULE_LICENSE("GPL");                  // tells that module bears free module
MODULE_AUTHOR("madhusudhan");           // Author name
MODULE_DESCRIPTION("moduleparameters"); // Description about the module
MODULE_ALIAS("madhu");                  // Another name of the module

static char *charvar = "madhusudhan";
static int intvar = 33;
/* Using the following macros, Variables are enabled to modified from command line.
module_param takes three arguments (var_name,type of variable,permission)*/

module_param(charvar, charp, S_IRUGO);
module_param(intvar, int, S_IRUGO);

// To initialize the module and load into kernel

static int __init hello_init(void)
{
    printk(KERN_ALERT "\n Hello World\n"); // KERN_ALERT is the priority message : Decides the seriousness of message
    printk(KERN_ALERT "\nThe value of charvar is %s\n", charvar);
    printk(KERN_ALERT "\nThe value of a intvar %d\n", intvar);

    return 0; // return 0 for sucessfull compilation
}

// To removes module from the kernel

static void __exit hello_exit(void)
{
    printk("\n bye world \n");
}

module_init(hello_init); // Module Initialization
module_exit(hello_exit); // Module De-Initialization
