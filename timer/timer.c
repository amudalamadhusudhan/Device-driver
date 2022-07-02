
// Header files begins //////////////////////////////////////////////////////////////////
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
// Header files ends //////////////////////////////////////////////////////////////////
#define timeout 1000
dev_t dev; // major number minor dynamic allocation //
static struct cdev char_cdev;
struct timer_list hc_timer;
unsigned int count = 0;

// function prototypes
static void __exit driverE(void);
static int __init driverI(void);
static int char_open(struct inode *inode, struct file *file);
static int char_release(struct inode *inode, struct file *file);
static ssize_t char_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t char_write(struct file *filp, const char __user *buf, size_t len, loff_t *off);
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .write = char_write,
    .open = char_open,
    .release = char_release,
    .read = char_read,

};
void timer_callback(struct timer_list *data)
{
    pr_info("timer callback funtion called [%d]\n", count++);
    mod_timer(&hc_timer, jiffies + msecs_to_jiffies(timeout));
}
static int char_open(struct inode *inode, struct file *file)
{
    pr_info("timer driver open function called\n");
    return 0;
}
static int char_release(struct inode *inode, struct file *file)
{
    pr_info("timer driver realease function called\n");
    return 0;
}
static ssize_t char_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
    pr_info("timer driver read function called\n");
    return 0;
}
static ssize_t char_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
    pr_info("timer driver write function called\n");
    return 0;
}

// To initialize the module and load into kernel

static int __init driverI(void)
{
    alloc_chrdev_region(&dev, 0, 3, "timer char dynamic driver");
    if ((alloc_chrdev_region(&dev, 0, 3, "timer char  dynamic driver")) < 0)
    {
        printk(KERN_ALERT "timer driver inserted unsussfuly\n");
        return -1;
    }
    printk(KERN_INFO "\n major =%d minor=%d\n", MAJOR(dev), MINOR(dev));

    // creating cdev structure;

    cdev_init(&char_cdev, &fops);
    // adding char driver to the system
    if ((cdev_add(&char_cdev, dev, 3)) < 0)
    {
        pr_err("cannot add the device to the system");
    }
    timer_setup(&hc_timer, timer_callback, 0);
    mod_timer(&hc_timer, jiffies + msecs_to_jiffies(timeout));
    printk(KERN_ALERT "timer char device driver inserted successfuly\n");
    return 0; // return 0 for sucessfull compilation
}

// To removes module from the kernel

static void __exit driverE(void)
{
    cdev_del(&char_cdev);
    unregister_chrdev_region(dev, 1);
    printk(KERN_ALERT "\n timer char  dynamic device driver removed successfully\n");
}

module_init(driverI); // Module Initialization
module_exit(driverE); // Module De-Initialization

MODULE_LICENSE("GPL");        // tells that module bears free module
MODULE_AUTHOR("madhusudhan"); // Author name
MODULE_DESCRIPTION("module"); // Description about the module
MODULE_ALIAS("madhu");        // Another name of the module
