/* Hello World Program */

// Header files begins //////////////////////////////////////////////////////////////////
#include <linux/init.h>   // Required header for initialization and clean up funtionalities
#include <linux/module.h> // This header contain the necessary stuff for the module
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#define mem_size 1024;
// Header files ends //////////////////////////////////////////////////////////////////

MODULE_LICENSE("GPL");        // tells that module bears free module
MODULE_AUTHOR("madhusudhan"); // Author name
MODULE_DESCRIPTION("module"); // Description about the module
MODULE_ALIAS("madhu");        // Another name of the module

dev_t dev = 0; // major number minor dynamic allocation
static struct cdev char_cdev;
uint8_t *kbuf;
// function prototypes
static void __exit driverE(void);
static int __init driverI(void);
static int char_open(struct inode *inode, struct file *file);
static int char_release(struct inode *inode, struct file *file);
static ssize_t char_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t char_write(struct file *filp, const char *buf, size_t len, loff_t *off);
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .write = char_write,
    .open = char_open,
    .release = char_release,
    .read = char_read,

};
static int char_open(struct inode *inode, struct file *file)
{
    pr_info("char driver open function called\n");
    return 0;
}
static int char_release(struct inode *inode, struct file *file)
{
    pr_info("char driver realease function called\n");
    return 0;
}
static ssize_t char_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
    if (copy_to_user(buf, kbuf, mem_size))
    {
        pr_err("data read error\n");
    }
    pr_info("char driver read done ...\n");
    return mem_size;
}
static ssize_t char_write(struct file *filp, const char *buf, size_t len, loff_t *off)
{

    if (copy_from_user(kbuf, buf, len))
    {
        pr_err("data write error\n");
    }
    pr_info("char driver write done ...\n");
    return len;
}
}

// To initialize the module and load into kernel

static int __init driverI(void)
{
    alloc_chrdev_region(&dev, 0, 1, "simple char dynamic driver");
    if ((alloc_chrdev_region(&dev, 0, 1, "simple char  dynamic driver")) < 0)
    {
        printk(KERN_ALERT "char driver inserted unsussfuly\n");
        return -1;
    }
    printk(KERN_INFO "\n major =%d minor=%d\n", MAJOR(dev), MINOR(dev));

    // creating cdev structure;
    cdev_init(&char_cdev, &fops);
    // adding char driver to the system
    if ((cdev_add(&char_cdev, dev, 1)) < 0)
    {
        pr_err("cannot add the device to the system");
    }
    if ((kbuf = kmalloc(mem_size, GFP_KERNAL)) == 0)
    {
        pr_err("cannot allocate the memory");
    }
    strcpy(kbuf, "madhusudhan");
    printk(KERN_ALERT "char device driver inserted successfuly\n");
    return 0; // return 0 for sucessfull compilation
}

// To removes module from the kernel

static void __exit driverE(void)
{
    kfree(kbuf);
    cdev_del(&char_cdev);
    unregister_chrdev_region(dev, 1);
    printk(KERN_ALERT "\n char  dynamic device driver removed successfully\n");
}

module_init(driverI); // Module Initialization
module_exit(driverE); // Module De-Initialization
