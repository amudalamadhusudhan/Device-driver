#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/types.h>
#include<linux/uaccess.h>
#include<linux/cdev.h>
#include<linux/timer.h>
#include<linux/jiffies.h>
#include<linux/gpio.h>
#include "timer.h"

#define SL timer
unsigned int wait_time=3000;
static struct timer_list led_timer;
void timer_callback_led_toggle(struct timer_list *timer);
static unsigned int gpioLED=6;
static bool gpioval=0;

dev_t dev;
struct cdev my_cdev;

int SL_open(struct inode *inode,struct file *filp);
long SL_ioctl(struct file *filp,unsigned int cmd,unsigned long argp);
int SL_release(struct inode *inode,struct file *filp);

struct file_operations fops=
{
    .owner          =   THIS_MODULE,
    .open           =   SL_open,
    .unlocked_ioctl =   SL_ioctl,
    .release       =   SL_release,
};

static int __init prog_init(void)
{
    int result;
    dev=MKDEV(30,0);
    result=register_chrdev_region(dev,1,"timer");
    if(result<0)
    {
        printk("\n cannot register major and minor number..!!\n");
        return -1;
    }
    printk("MAJOR : MINOR OF TIMER DRIVER %d : %d\n",MAJOR(dev),MINOR(dev));

    cdev_init(&my_cdev,&fops);

    if(cdev_add(&my_cdev,dev,1)<0)
    {
        printk("\n cannot add major number and cdev..!!\n");
        return -1;
    }
    if(!gpio_is_valid(gpioLED))
    {
        printk("\n invalid GPIO..!\n");
        return -ENODEV;
    }
    gpio_request(gpioLED,"GPIO_6");
    gpio_direction_output(gpioLED,0);
    gpio_export(gpioLED,false);

    timer_setup(&led_timer,timer_callback_led_toggle,0);//init timer 

    int is_active=mod_timer(&led_timer,jiffies + msecs_to_jiffies(wait_time));

    if(is_active)
    {
        printk("\n timer failed..!!\n");
        return -1;
    }
    printk("\n DRIVER LOADED AND TIMER INITIALIZED.!\n");
    return 0;
}

static void __exit prog_exit(void)
{
    del_timer(&led_timer);
    gpio_unexport(gpioLED);
    unregister_chrdev_region(dev,1);
    cdev_del(&my_cdev);
    printk("\n DRIVER UNLOADED..!!\n");
}
module_init(prog_init);
module_exit(prog_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SRA");

int SL_open(struct inode *inode,struct file *filp)
{
    printk("\n OPEN SYSTEM CALL...\n");
    return 0;
}
int SL_release(struct inode *inode,struct file *filp)
{
    printk("\n CLOSE SYSTEM CALL...\n");
    return 0;
}
long SL_ioctl(struct file *filp,unsigned int cmd,unsigned long argp)
{
    long result;
    switch(cmd)
    {
        case set_periodicity:
            result=copy_from_user(&wait_time,(int *)argp,sizeof(wait_time));
            if(result==0)
            {
                return result;
            }
            else
            {
                printk("\n error in set periodicity..!\n");
            }
            break;
/*      case get_periodicity:
            result=copy_to_user((int *)argp,(int *)&wait_time,sizeof(wait_time));
            if(result>0)
            {
                printk("\n error in get peroidicity..!\n");
            }
            break; */
    }
    return result;
}
void timer_callback_led_toggle(struct timer_list *timer)
{
    gpioval=!gpioval;
    gpio_set_value(gpioLED,gpioval);
    int led_value=gpio_get_value(gpioLED);
    unsigned long jiffies_for_msecs=msecs_to_jiffies(wait_time);
    int is_active=mod_timer(&led_timer,jiffies+jiffies_for_msecs);
    if(is_active)
    {
        printk("\n error in changing value..!\n");
        return ;
    }
}