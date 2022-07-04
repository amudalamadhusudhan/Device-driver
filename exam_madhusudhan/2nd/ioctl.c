
// Header files begins //////////////////////////////////////////////////////////////////
#include <linux/init.h>   // Required header for initialization and clean up funtionalities
#include <linux/module.h> // This header contain the necessary stuff for the module
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/gpio.h> 
// Header files ends //////////////////////////////////////////////////////////////////

#define WR_VALUE _IOW('a', 'a', int32_t *)
#define RD_VALUE _IOR('a', 'b', int32_t *)

int32_t value1 = 0;
int32_t value2 = 0;
int32_t value = 0;
int32_t oper = 0;

dev_t dev = 0; // major number minor dynamic allocation
static struct cdev char_cdev;
// function prototypes
static void __exit driverE(void);
static int __init driverI(void);
static long char_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);
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
    .unlocked_ioctl = char_ioctl,

};
static long char_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{

    static int count = 0;
    switch (cmd)
    {

    case WR_VALUE:
        if (count == 0)
        {
            copy_from_user(&oper, (int32_t *)arg, sizeof(oper));
            printk(KERN_INFO "oper = %d\n", oper);
            break;
        }
        else if (count == 1)
        {
            copy_from_user(&value1, (int32_t *)arg, sizeof(value1));
            printk(KERN_INFO "value1 = %d\n", value1);
            break;
        }
        else if (count == 2)
        {
            copy_from_user(&value2, (int32_t *)arg, sizeof(value2));
            printk(KERN_INFO "value2 = %d\n", value2);
            break;
        }
    case RD_VALUE:
        if (oper == 1)
            value = value1 + value2;
        else if (oper == 2)
            value = value1 - value2;
        else if (oper == 3)
            value = (value1 * value2);
        else if (oper == 4)
            value = value1 / value2;
        else
            break;
        copy_to_user((int32_t *)arg, &value, sizeof(value));
        break;
    }

    count += 1;
    if (count == 3)
        count = 0;
    printk("calculation sucssfull result = %d\n", value);
    return 0;
}

static int char_open(struct inode *inode, struct file *file)
{
    pr_info("char cal driver open function called\n");
    return 0;
}
static int char_release(struct inode *inode, struct file *file)
{
    pr_info("char cal driver realease function called\n");
    return 0;
}
static ssize_t char_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
     uint8_t gpio_state = 0;
  
  //reading GPIO value
  gpio_state = gpio_get_value(GPIO_21);
  
  //write to user
  len = 1;
  if( copy_to_user(buf, &gpio_state, len) > 0) {
    pr_err("ERROR: Not all the bytes have been copied to user\n");
  }
  
  pr_info("Read function : GPIO_21 = %d \n", gpio_state);
    pr_info("char cal driver read function called\n");
    return 0;
}
static ssize_t char_write(struct file *filp, const char *buf, size_t len, loff_t *off)
{

  if( copy_from_user( rec_buf, buf, len ) > 0) {
    pr_err("ERROR: Not all the bytes have been copied from user\n");
  }
  
  pr_info("Write Function : GPIO_21 Set = %c\n", rec_buf[0]);
  
  if (rec_buf[0]=='1') {
    //set the GPIO value to HIGH
    gpio_set_value(GPIO_21, 1);
  } else if (rec_buf[0]=='0') {
    //set the GPIO value to LOW
    gpio_set_value(GPIO_21, 0);
  } else {
    pr_err("Unknown command : Please provide either 1 or 0 \n");
  }
  
  return len;
    pr_info("char cal driver write function called\n");
    return 0;
}

// To initialize the module and load into kernel

static int __init driverI(void)
{
    alloc_chrdev_region(&dev, 0, 3, "cal char dynamic driver");
    if ((alloc_chrdev_region(&dev, 0, 3, "cal char  dynamic driver")) < 0)
    {
        printk(KERN_ALERT "cal driver inserted unsussfuly\n");
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
//Checking the GPIO is valid or not
  if(gpio_is_valid(GPIO_21) == false){
    pr_err("GPIO %d is not valid\n", GPIO_21);
    goto r_device;
  }
  
  //Requesting the GPIO
  if(gpio_request(GPIO_21,"GPIO_21") < 0){
    pr_err("ERROR: GPIO %d request\n", GPIO_21);
    goto r_gpio;
  }
  
  //configure the GPIO as output
  gpio_direction_output(GPIO_21, 0);
  
  /* Using this call the GPIO 21 will be visible in /sys/class/gpio/
  ** Now you can change the gpio values by using below commands also.
  ** echo 1 > /sys/class/gpio/gpio21/value  (turn ON the LED)
  ** echo 0 > /sys/class/gpio/gpio21/value  (turn OFF the LED)
  ** cat /sys/class/gpio/gpio21/value  (read the value LED)
  ** 
  ** the second argument prevents the direction from being changed.
  */
  gpio_export(GPIO_21, false);
  
  pr_info("Device Driver Insert...Done!!!\n");
  return 0;
 
    printk(KERN_ALERT "cal char device driver inserted successfuly\n");
    return 0; // return 0 for sucessfull compilation
    r_gpio:
  gpio_free(GPIO_21);
r_device:
  device_destroy(dev_class,dev);
r_class:
  class_destroy(dev_class);
r_del:
  cdev_del(&etx_cdev);
r_unreg:
  unregister_chrdev_region(dev,1);
}

// To removes module from the kernel

static void __exit driverE(void)
{
     gpio_unexport(GPIO_21);
  gpio_free(GPIO_21);
    cdev_del(&char_cdev);
    unregister_chrdev_region(dev, 1);
    printk(KERN_ALERT "\n char  dynamic device driver removed successfully\n");
}

module_init(driverI);         // Module Initialization
module_exit(driverE);         // Module De-Initialization
MODULE_LICENSE("GPL");        // tells that module bears free module
MODULE_AUTHOR("madhusudhan"); // Author name
MODULE_DESCRIPTION("module"); // Description about the module
MODULE_ALIAS("madhu");        // Another name of the module