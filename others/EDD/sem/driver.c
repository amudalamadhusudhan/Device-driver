#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/types.h>
#include<linux/uaccess.h>
#include<linux/kthread.h>
#include<linux/sched.h>
#include<linux/delay.h>
#include<linux/seqlock.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/completion.h>

//seqlock declaration

DEFINE_SEMAPHORE(sem);
DECLARE_COMPLETION(read);
DECLARE_COMPLETION(write);
dev_t dev;
static struct cdev my_cdev;
char Kbuff[80]; 

//Function declaration:
int CAN_open(struct inode *inode,struct file *filp);    
ssize_t CAN_read(struct file *filp,char __user *ubuff,size_t count,loff_t *offp);
ssize_t CAN_write(struct file *filp, const char __user *ubuff,size_t count,loff_t *offp);
int CAN_release(struct inode *inode,struct file *filp);

struct file_operations fops=
{
    .owner  =   THIS_MODULE,
    .open   =   CAN_open,
    .read   =   CAN_read,
    .write  =   CAN_write,
    .release=   CAN_release,
};

int CAN_open(struct inode *inode,struct file *filp)
{
    printk("\n OPEN FUNCTION..\n");
    return 0;
}
int CAN_release(struct inode *inode,struct file *filp)
{
    printk("\n CLOSE FUNCTION..\n");
    return 0;
}
ssize_t CAN_read(struct file *filp,char __user *Ubuff,size_t count,loff_t *offp)
{
unsigned long result;
ssize_t retval;
    wait_for_completion_interruptible(&write);
result = copy_to_user((char *)Ubuff, (char *)Kbuff,sizeof(Kbuff));
    complete(&read);
if(result==0)
    {
            printk(KERN_ALERT "\n DATA READED  from the kernal and provided to user SUCESSFULLY!! \n");
            retval=count;
            return retval;
    }
    else if(result>0)
    {
         printk(KERN_ALERT "\n Part Data!! \n");
            retval=count-result;
            return retval;
    }
    else
    {
        printk(KERN_ALERT "\n Error DATA!! \n");
            retval=-EFAULT;
            return retval;
    }
    // spin_unlock(&etx_spinlock);

}  
ssize_t CAN_write(struct file *filp,const char __user *Ubuff,size_t count,loff_t *offp)
{
unsigned long result;
ssize_t retval;
   
    down(&sem);
    result = copy_from_user((char *)Kbuff,(char *)Ubuff, count);
    complete(&write);
    wait_for_completion_interruptible(&read);
        up(&sem);
    if(result==0)
        {
            printk(KERN_ALERT "\n DATA write SUCESSFULLY!! \n");
            printk(KERN_ALERT "\n data is %s \n",Kbuff);
            retval=count;
            return retval;
    }
    else if(result>0)
    {
         printk(KERN_ALERT "\n Part Data !! \n");
           printk(KERN_ALERT "\n data from user is  %s \n",Kbuff);
            retval=count-result;
            return retval;
    }
    else
    {
         printk(KERN_ALERT "\n Error DATA!! \n");
            retval=-EFAULT;
            return (-1);
    }
    //    spin_unlock(&etx_spinlock);

} 

static int __init prog_init(void)
{
    if((alloc_chrdev_region(&dev,0,1,"SEM"))<0)
    {
        printk("\n cannot create major number..\n");
        return -1;
    }
    int major,minor;
major= MAJOR(dev);
minor =  MINOR(dev);

printk("\n Major Number: %d\n", major);
printk("\n MInor Number: %d\n", minor);
    // cdev structure

    cdev_init(&my_cdev,&fops);

    // addind cdev and major

    if((cdev_add(&my_cdev,dev,1))<0)
    {
        printk("\n cannot add cdev and major..\n");
        unregister_chrdev_region(dev,1);
        return -1;
    }

    printk("\n DRIVER LOADED..\n");
    return 0;
}
static void __exit prog_exit(void)
{
    //stop the thread
    // kthread_stop(kthread_1);
    // kthread_stop(kthread_2);
    unregister_chrdev_region(dev,1);
    cdev_del(&my_cdev);
    printk("\n DRIVER UNLOADED..\n");
}
module_init(prog_init);
module_exit(prog_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ashutosh");