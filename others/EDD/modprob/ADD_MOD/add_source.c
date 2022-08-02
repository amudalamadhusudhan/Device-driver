#include<linux/init.h>  // Required header fot the Initiallization and Cleanup Functionalities
#include<linux/module.h>  // this Header contains the necessary stuff for the module
#include<linux/moduleparam.h>  // This header allows the passing of parameter to the modules during insertion


MODULE_LICENSE("GPL");  // Macros that decide the license of the module
MODULE_AUTHOR("KAJOL");
MODULE_DESCRIPTION("Export symbol module");

static int my_add(int a, int b)
{
    return (a + b);

}

/* Command to export symbol into kernel symbol table */
EXPORT_SYMBOL(my_add);

// Initialization function for the program
static int __init prog_init(void)
{
    printk(KERN_ALERT "Initialization of module\n");

    return 0;

}

// cleanup function
static void __exit prog_exit(void)
{
    printk(KERN_ALERT "exit from Module\n");
}

// MACROS that allow the user to override the names of the above mentioned functions with thier own choice....
module_init(prog_init);  // for INITIALIZATION function
module_exit(prog_exit);  // for CLEANUP function


