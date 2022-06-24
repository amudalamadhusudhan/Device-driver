/* Hello World Program */

// Header files begins //////////////////////////////////////////////////////////////////
#include <linux/init.h>   // Required header for initialization and clean up funtionalities
#include <linux/module.h> // This header contain the necessary stuff for the module
#include <linux/kernel.h>
// Header files ends //////////////////////////////////////////////////////////////////

MODULE_LICENSE("GPL");        // tells that module bears free module
MODULE_AUTHOR("madhusudhan"); // Author name
MODULE_DESCRIPTION("madhu");  // Description about the module
MODULE_ALIAS("madhu");        // Another name of the module

char s[10] = "module";
int a = 10;

/* Using the following macros, Variables are enabled to modified from command line.
module_param takes three arguments (var_name,type of variable,permission)*/

// module_param(s, charp, S_IRUGO);
// module_param(a, int, S_IRUGO);

// To initialize the module and load into kernel

static int __init hello_init(void)
{
    printk(KERN_ALERT "\n Hello World\n"); // KERN_ALERT is the priority message : Decides the seriousness of message
    printk(KERN_ALERT "\nThe value of s is %s\n", s);
    printk(KERN_ALERT "\nThe value of a is %d\n", a);

    return 0; // return 0 for sucessfull compilation
}

// To removes module from the kernel

static void __exit hello_exit(void)
{
    printk("\n bye world \n");
}

module_init(hello_init); // Module Initialization
module_exit(hello_exit); // Module De-Initialization
