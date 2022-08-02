

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
#include<linux/slab.h>    //kmalloc()
#include<linux/device.h>

//delarations:
dev_t dev;
struct cdev my_cdev;
seqlock_t lock;


int AUS_open(struct inode *inode,struct file *filp);
ssize_t AUS_read(struct file *filp,char __user *ubuff,size_t count,loff_t *offp);
ssize_t AUS_write(struct file *filp, const char __user *ubuff,size_t count,loff_t *offp);
int AUS_release(struct inode *inode,struct file *filp);

struct file_operations fops=
{
    .owner  =   THIS_MODULE,
    .open   =   AUS_open,
    .read   =   AUS_read,
    .write  =   AUS_write,
    .release=   AUS_release,
};

static int __init prog_init(void)
{
    if((alloc_chrdev_region(&dev,30,1,"AUS"))<0)
    {
        printk("\n Cannot create major number..\n");
        return -1;
    }
    printk("\n MAJOR : MINOR %d:%d\n",MAJOR(dev),MINOR(dev));
    // adding cdev
    cdev_init(&my_cdev,&fops);
    // adding major and cdev
    if((cdev_add(&my_cdev,dev,1))<0)
    {
        printk("\n Cannot add major number..\n");
        unregister_chrdev_region(dev,1);
        return -1;
    }
    // seqlock init
    seqlock_init(&lock);
    printk("\n DEVICE LOADED\n");
    return 0;
}
static void __exit prog_exit(void)
{
    unregister_chrdev_region(dev,1);
    cdev_del(&my_cdev);
    printk("\n DEVICE UNLOADED\n");
}
module_init(prog_init);
module_exit(prog_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ASHUTOSH");

int AUS_open(struct inode *inode,struct file *filp)
{
    printk("\n OPEN CALL\n");
    return 0;
}
int AUS_release(struct inode *inode,struct file *filp)
{
    printk("\n CLOSE CALL\n");
    return 0;
}

//global declaration:


char kbuff[40];


ssize_t AUS_write(struct file *filp,const char __user *ubuff,size_t count,loff_t *offp)
{
    unsigned long result;
    ssize_t retval;
    write_seqlock(&lock);
    result=copy_from_user((char*)kbuff,(char*)ubuff,count);
    write_sequnlock(&lock);
    if(result==0)
    {
        printk(KERN_ALERT "\n MESSAGE FROM USER..\n...%s....\n",ubuff);
        printk(KERN_INFO  "\n DATA RECEIVED COMPLETED..\n");
        retval=count;
        return retval;
    }
    else if(result>0)
    {  
        printk(KERN_ALERT "\n MESSAGE FROM USER..\n...%s....\n",ubuff);
        printk(KERN_ALERT "\n THE PART OF DATA IS RECEIVED..\n ");
        retval=(count-result);
        return retval;
    }
    else
    {
        printk(KERN_ALERT "\n ERROR IN WRITING");
        retval=-EFAULT;
        return retval;
    }
}
ssize_t AUS_read(struct file *filp,char __user *ubuff,size_t count,loff_t *offp)
{
    unsigned int seq_no;
    unsigned char read_val[40];
    unsigned long result;
    ssize_t retval;
    do
    {
        seq_no=read_seqbegin(&lock);
   //   read_val[40]=kbuff[40];
        strcpy(read_val,kbuff);
    }while(read_seqretry(&lock,seq_no));
    result=copy_to_user((char*)ubuff,(char*)read_val,count);
    if(result==0)
    {
        printk(KERN_ALERT "\n MESSAGE TO USER..\n...%s....\n",kbuff);
        printk(KERN_INFO  "\n DATA SEND COMPLETED..\n");
        retval=count;
        return retval;
    }
    else if(result>0)
    {  
        printk(KERN_ALERT "\n MESSAGE TO USER..\n...%s....\n",kbuff);
        printk(KERN_ALERT "\n THE PART OF DATA IS SENDED..\n ");
        retval=(count-result);
        return retval;
    }
    else
    {
        printk(KERN_ALERT "\n ERROR IN READING");
        retval=-EFAULT;
        return retval;
    }
}