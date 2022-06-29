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
#include <linux/kthread.h>
#include <linux/wait.h>

// Header files ends //////////////////////////////////////////////////////////////////

MODULE_LICENSE("GPL");        // tells that module bears free module
MODULE_AUTHOR("madhusudhan"); // Author name
MODULE_DESCRIPTION("module"); // Description about the module
MODULE_ALIAS("madhu");        // Another name of the module

dev_t dev = 0; // major number minor dynamic allocation
static struct cdev wq_cdev;
static struct class *dev_class;
static struct task_struct *wait_thread;
wait_queue_head_t wait_queue_wq;
int wait_queue_flag = 0;
uint8_t read_count = 0, write_count = 0;
// function prototypes
static int wait_function(void *unused);
static void __exit driverE(void);
static int __init driverI(void);
static int wq_open(struct inode *inode, struct file *file);
static int wq_release(struct inode *inode, struct file *file);
static ssize_t wq_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t wq_write(struct file *filp, const char *buf, size_t len, loff_t *off);
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .write = wq_write,
    .open = wq_open,
    .release = wq_release,
    .read = wq_read,

};
static int wait_function(void *unused)
{
    while (1)
    {
        pr_info("waiting for the event\n");
        wait_event_interruptible(wait_queue_wq, wait_queue_flag != 0);
        if (wait_queue_flag == 2)
        {
            pr_info(".......event from the exit function \n");
            return 0;
        }
        if (wait_queue_flag == 1)
        {
            pr_info(".......event from the read function= %d \n", ++read_count);
            return 0;
        }
        if (wait_queue_flag == 3)
        {
            pr_info(".......event from the write function= %d \n", ++write_count);
            return 0;
        }
        wait_queue_flag = 0;
    }
    return 0;
}
static int wq_open(struct inode *inode, struct file *file)
{
    pr_info("wq driver open function called\n");
    return 0;
}
static int wq_release(struct inode *inode, struct file *file)
{
    pr_info("wq driver realease function called\n");
    return 0;
}
static ssize_t wq_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
    pr_info("read section");
    wait_queue_flag = 1;
    wake_up_interruptible(&wait_queue_wq);

    // pr_info("wq driver read done ...\n");
    return 0;
}
static ssize_t wq_write(struct file *filp, const char *buf, size_t len, loff_t *off)
{
    pr_info("write section");
    wait_queue_flag = 3;
    wake_up_interruptible(&wait_queue_wq);

    // pr_info("wq driver read done ...\n");
    return len;
}

// To initialize the module and load into kernel

static int __init driverI(void)
{
    alloc_chrdev_region(&dev, 0, 1, "simple wq dynamic driver");
    if ((alloc_chrdev_region(&dev, 0, 1, "simple wq  dynamic driver")) < 0)
    {
        printk(KERN_ALERT "wq driver inserted unsussfuly\n");
        return -1;
    }
    printk(KERN_INFO "\n major =%d minor=%d\n", MAJOR(dev), MINOR(dev));

    // creating cdev structure;
    cdev_init(&wq_cdev, &fops);
    // adding wq driver to the system
    if ((cdev_add(&wq_cdev, dev, 1)) < 0)
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
    init_waitqueue_head(&wait_queue_wq);
    wait_thread = kthread_create(wait_function, NULL, "waitThread");
    if (wait_thread)
    {
        pr_info("thread creation successfull\n");
        wake_up_process(wait_thread);
    }
    else
    {
        pr_info("thread creation failed\n");
    }

    printk(KERN_ALERT "wq device driver inserted successfuly\n");
    return 0; // return 0 for sucessfull compilation
}

// To removes module from the kernel

static void __exit driverE(void)
{
    wait_queue_flag = 2;
    wake_up_interruptible(&wait_queue_wq);
    device_destroy(dev_class, dev);
    cdev_del(&wq_cdev);
    unregister_chrdev_region(dev, 1);
    printk(KERN_ALERT "\n wq  dynamic device driver removed successfully\n");
}

module_init(driverI); // Module Initialization
module_exit(driverE); // Module De-Initialization
