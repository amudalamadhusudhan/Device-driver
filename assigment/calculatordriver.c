
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
#include <linux/semaphore.h>
// Header files ends //////////////////////////////////////////////////////////////////
#define size 1024
dev_t dev; // major number minor dynamic allocation //
static struct cdev char_cdev;
struct semaphore my_sema;
unsigned int add, sub, mul, div;
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
static int char_open(struct inode *inode, struct file *file)
{
    pr_info("calc open function called\n");
    return 0;
}
static int char_release(struct inode *inode, struct file *file)
{
    pr_info("calc realease function called\n");
    return 0;
}
static ssize_t char_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
    if (copy_to_user((char *)buf, &add, sizeof(add)) &&
        copy_to_user((char *)buf, &sub, sizeof(sub)) &&
        copy_to_user((char *)buf, &mul, sizeof(mul)) &&
        copy_to_user((char *)buf, &div, sizeof(div)) != 0)
    {
        pr_err("calc data read error\n");
    }
    else
    {
        printk("sucuss of reading calc driver read done ...\n");
        printk("\n calc add_read  %d\n", add);
        printk("\n calc sub_read  %d\n", sub);
        printk("\n calc mul_read  %d\n", mul);
        printk("\n calc div_read  %d\n", div);

        return len;
    }
    return 0;

    return 0;
}
static ssize_t char_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
    int kbuff[2];
    int n1, n2;
    if (copy_from_user((char *)kbuff, (char *)buf, sizeof(kbuff)) != 0)
    {
        pr_err("data write error\n");
    }
    else
    {
        printk("success in writing from the user to kernal\n");
        n1 = kbuff[0];
        n2 = kbuff[1];
        add = n1 + n2;
        sub = n1 - n2;
        mul = n1 * n2;
        div = n1 / n2;
        printk("success in writing from the user to kernal result =%d\n", add);
        printk("success in writing from the user to kernal result =%d\n", sub);
        printk("success in writing from the user to kernal result =%d\n", mul);
        printk("success in writing from the user to kernal result =%d\n", div);
        return len;
    }
    return 0;
}

// To initialize the module and load into kernel

static int __init driverI(void)
{
    alloc_chrdev_region(&dev, 0, 4, "calc dynamic driver");
    if ((alloc_chrdev_region(&dev, 0, 4, "calc  dynamic driver")) < 0)
    {
        printk(KERN_ALERT "sem driver inserted unsussfuly\n");
        return -1;
    }
    printk(KERN_INFO "\n major =%d minor=%d\n", MAJOR(dev), MINOR(dev));

    // creating cdev structure;

    cdev_init(&char_cdev, &fops);
    // adding char driver to the system
    if ((cdev_add(&char_cdev, dev, 4)) < 0)
    {
        pr_err("cannot the device to the system");
    }
    printk(KERN_ALERT "calc device driver inserted successfuly\n");
    return 0; // return 0 for sucessfull compilation
}

// To removes module from the kernel

static void __exit driverE(void)
{
    cdev_del(&char_cdev);
    unregister_chrdev_region(dev, 1);
    printk(KERN_ALERT "\n calc dynamic device driver removed successfully\n");
}

module_init(driverI); // Module Initialization
module_exit(driverE); // Module De-Initialization

MODULE_LICENSE("GPL");        // tells that module bears free module
MODULE_AUTHOR("madhusudhan"); // Author name
MODULE_DESCRIPTION("module"); // Description about the module
MODULE_ALIAS("madhu");        // Another name of the module
