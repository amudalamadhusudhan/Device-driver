#include<linux/init.h>  // Required header fot the Initiallization and Cleanup Functionalities
#include<linux/module.h>  // this Header contains the necessary stuff for the module
#include<linux/moduleparam.h>  // This header allows the passing of parameter to the modules during insertion


MODULE_LICENSE("GPL");  // Macros that decide the license of the module
MODULE_AUTHOR("ashutosh");
MODULE_DESCRIPTION("A parameter passing module");

/* variables are declared as static to keep their scope local to this module */

static char * charvar = "Module";
static int intvar = 10;


module_param(charvar, charp, S_IRUGO);     // charp = character pointer
module_param(intvar, int, S_IRUGO);


// Initialization function for the program
static int __init param_init(void)
{
    printk(KERN_ALERT "In Init Module\n");
    printk(KERN_ALERT "The value of charvar is %s\n", charvar);

    return 0;

}

// cleanup function
static void __exit param_exit(void)
{
    printk(KERN_ALERT "Goodbye, Module\n");
}

// MACROS that allow the user to override the names of the above mentioned functions with thier own choice....
module_init(param_init);  // for INITIALIZATION function
module_exit(param_exit);  // for CLEANUP function


