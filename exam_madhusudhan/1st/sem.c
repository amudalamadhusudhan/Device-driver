

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
#define size 50
dev_t dev; // major number minor dynamic allocation //
static struct cdev char_cdev;
struct semaphore my_sema;
static struct class *dev_class;
wait_queue_head_t wait_queue_wq;
int wait_queue_flag = 0;
unsigned int op_result;
// function prototypes
static void __exit driverE(void);
static int __init driverI(void);
static int wait_function(void *unused);
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
    pr_info("sem driver open function called\n");
    return 0;
}
static int char_release(struct inode *inode, struct file *file)
{
    pr_info("sem driver realease function called\n");
    return 0;
}
static ssize_t char_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
    printk("sem driver read function called\n");
     
    int r;
    r = copy_to_user((char *)buf, &op_result, sizeof(op_result));
    if (r == 0)
    {
        printk("\n sucuss in reading data from the kernal to usr\n");

        printk("\n sucuss in reading data from the kernal to usr %d\n", op_result);
        up(&my_sema);
       wake_up(&wait_queue_wq);
        return len;
    }
    else
    {
        printk(" errot in reading data from  kernal to usr\n");
        return -1;
    }

    return 0;
}
static ssize_t char_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
    int flag=0;
    down_trylock(&my_sema);
     wait_queue_flag = 3;
        printk("\nsem driver write function called\n");
    int kbuff[2];
    int r, n1, n2;
    r = copy_from_user((char *)kbuff, (char *)buf, sizeof(kbuff));
    if (r == 0)
    {
        printk("success in writing from the user to kernal\n");
        n1 = kbuff[0];
        n2 = kbuff[1];
        op_result = n1 + n2;
        flag=0;
        printk("success in writing from the user to kernal result =%d\n", op_result);
        return len;
    }
    else
    {
        printk("error in writing data from user to kernal");
        return -1;
    }

    return 0;
}

// To initialize the module and load into kernel

static int __init driverI(void)
{
    alloc_chrdev_region(&dev, 0, 3, "sem char dynamic driver");
    if ((alloc_chrdev_region(&dev, 0, 3, "sem char  dynamic driver")) < 0)
    {
        printk(KERN_ALERT "sem driver inserted unsussfuly\n");
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
     if ((dev_class = class_create(THIS_MODULE, "wq_class")) == NULL)
    {
        pr_err("cannot create the class to the system");
    }
    if ((device_create(dev_class, NULL, dev, NULL, "wq_device")) == NULL)
    {
        pr_err("cannot create the device to the system");
    }
    sema_init(&my_sema, 1);
    init_waitqueue_head(&wait_queue_wq);
    printk(KERN_ALERT "sema char device driver inserted successfuly\n");
    return 0; // return 0 for sucessfull compilation
}

// To removes module from the kernel

static void __exit driverE(void)
{
       wake_up_interruptible(&wait_queue_wq);
    cdev_del(&char_cdev);
    unregister_chrdev_region(dev, 1);
    printk(KERN_ALERT "\n sema char  dynamic device driver removed successfully\n");
}

module_init(driverI); // Module Initialization
module_exit(driverE); // Module De-Initialization

MODULE_LICENSE("GPL");        // tells that module bears free module
MODULE_AUTHOR("madhusudhan"); // Author name
MODULE_DESCRIPTION("module"); // Description about the module
MODULE_ALIAS("madhu");        // Another name of the module