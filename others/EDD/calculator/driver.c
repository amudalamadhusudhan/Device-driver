#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#define MAX_DEVICES 4
#define SIZE 12

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ashutosh");
MODULE_DESCRIPTION("DEVICE DRIVER PROGRAM WITH MULTIPLE NODES");

static int Kbuffer[SIZE];
static int Ubuffer[SIZE];
int SUM,SUB,DIV,MUL;
//structure defined for each device
struct char_device_data
{
    //name of each device
    const char *name; 
    // char dev structure for each device
    struct cdev cdev;
};

//Structure defined for driver
struct char_driver_data
{
    int total_devices;
    dev_t deviceNumber;
    struct class *myclass;
    struct device *mydevice;
    struct char_device_data cd[MAX_DEVICES];
};

struct char_driver_data chr_drv_data={
    .total_devices = MAX_DEVICES,
    .cd={
        [0]={
            .name = "ADD"
        },
        [1]={
            .name = "SUB"
        },
        [2]={
            .name = "MUL"
        },
        [3]={
            .name = "DIV"
        }
    }
};




//ADD READ
ssize_t ADDread(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
return 0;
}

//ADD Write
ssize_t ADDwrite(struct file *filp, const char __user *Ubuffer,size_t count, loff_t *f_pos)
{
copy_from_user((int *)Kbuffer,(int *)Ubuffer,count);
printk("num1 %d \n num2 %d \n", Kbuffer[0],Kbuffer[1]);
SUM = Kbuffer[0]+Kbuffer[1];
printk("SUM : %d",SUM);
return 0;
}
/////////////////////////SUB DRIVER//////////////////////////////////////////////////////////////////
//SUB READ
ssize_t SUBread(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
return 0;
}

//SUB Write
ssize_t SUBwrite(struct file *filp, const char __user *Ubuffer,size_t count, loff_t *f_pos)
{
copy_from_user((int *)Kbuffer,(int *)Ubuffer,count);
printk("num1 %d \n num2 %d \n", Kbuffer[0],Kbuffer[1]);
SUB = Kbuffer[0]-Kbuffer[1];
printk("Sub : %d",SUB);
return 0;
}
/////////////////////////MULTIPLY DRIVER////////////////////////////////////////////////////////////////
//MUL READ
ssize_t MULread(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
return 0;
}

//MUL Write
ssize_t MULwrite(struct file *filp, const char __user *Ubuffer,size_t count, loff_t *f_pos)
{
copy_from_user((int *)Kbuffer,(int *)Ubuffer,count);
printk("num1 %d \n num2 %d \n", Kbuffer[0],Kbuffer[1]);
MUL = Kbuffer[0]*Kbuffer[1];
printk("Mul : %d",MUL);
return 0;
}
/////////////////////////DIVIDE DRIVER////////////////////////////////////////////////////////////////
//DIV READ
ssize_t DIVread(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
return 0;
}

//DIV Write
ssize_t DIVwrite(struct file *filp, const char __user *Ubuffer,size_t count, loff_t *f_pos)
{
copy_from_user((int *)Kbuffer,(int *)Ubuffer,count);
printk("num1 %d \n num2 %d \n", Kbuffer[0],Kbuffer[1]);
DIV = Kbuffer[0] / Kbuffer[1];
printk("DIV_2222: %d",DIV);
return 0;
}

//////////////////////////////////////////////////////////OPEN OPERATION/////////////////////////////////
int char_dev_open(struct inode *inode, struct file *filp)
{
int minor;
struct char_device_data *cd;
/*find out on which device file open was attempted by the
user space*/
minor = MINOR(inode->i_rdev);
printk("Minor access = %d\n",minor);
struct file_operations	*new_fops=filp->f_op;

switch(minor)
{
    case 0:
           new_fops->read=ADDread;
           new_fops->write=ADDwrite;
           break;
    case 1:
           new_fops->read=SUBread;
           new_fops->write=SUBwrite;
           break;
    case 2:
           new_fops->read=MULread;
           new_fops->write=MULwrite;
           break;
    case 3:
           new_fops->read=DIVread;
           new_fops->write=DIVwrite;
           break; 
    default:
           return 0;
}

//get device's private data structure/
cd = container_of(inode->i_cdev,struct char_device_data,cdev);
/*to supply device private data to other methods of the
driver*/
filp->private_data = cd;
printk("open was successful\n");
return 0;
}

////////////////////////////////////////////////////RELEASE OPERATION///////////////////////////////////////
int char_dev_release(struct inode *inode, struct file *filp)
{
printk("release was successful\n");
return 0;
}

struct file_operations fops=
{
.open = char_dev_open,
.release = char_dev_release,
.read = ADDread,
.write = ADDwrite,
.owner = THIS_MODULE
};

static int cdriver_init(void)
{
    int ret;
    int i;
    ret = alloc_chrdev_region(&chr_drv_data.deviceNumber,0,MAX_DEVICES,"CalC");
    if(ret<0)
    {
        printk("Alloc chedev failed\n");
        goto out;
    }    
    //Device Class Creation
    chr_drv_data.myclass= class_create(THIS_MODULE,"CalC_class");
    if(IS_ERR(chr_drv_data.myclass))
    {
        printk("Class Creation failed!\n");
        ret = PTR_ERR(chr_drv_data.myclass);
        goto unreg_chrdev;
    }

    for(i=0; i<MAX_DEVICES;i++)
    {   

        printk("Device Number MAJOR :%d\n MINOR :%d",
        MAJOR(chr_drv_data.deviceNumber),MINOR(chr_drv_data.deviceNumber+i));
        cdev_init(&chr_drv_data.cd[i].cdev,&fops);
        ret = cdev_add(&chr_drv_data.cd[i].cdev,chr_drv_data.deviceNumber + i,1);
        if(ret<0)
        {
            printk("Cdev add failed\n");
            goto cdev_del;
        }
    }
    

    chr_drv_data.mydevice =device_create(chr_drv_data.myclass,NULL,chr_drv_data.deviceNumber,NULL,"ADD");
    chr_drv_data.mydevice =device_create(chr_drv_data.myclass,NULL,chr_drv_data.deviceNumber+1,NULL,"SUB");
    chr_drv_data.mydevice =device_create(chr_drv_data.myclass,NULL,chr_drv_data.deviceNumber+2,NULL,"MUL");
    chr_drv_data.mydevice =device_create(chr_drv_data.myclass,NULL,chr_drv_data.deviceNumber+3,NULL,"DIV");
    
    pr_info("MODULE init was successfull\n");
    return 0;

    cdev_del:
        for(;i>=0;i--)
        {
            device_destroy(chr_drv_data.myclass,chr_drv_data.deviceNumber+i);
            cdev_del(&chr_drv_data.cd[i].cdev);
        }
        class_destroy(chr_drv_data.myclass);
        return 0;

    unreg_chrdev:
        unregister_chrdev_region(chr_drv_data.deviceNumber,MAX_DEVICES);
        return 0;

    out:
        return ret;
}

static void cdriver_exit(void)
{
int i;
for(i=0;i<MAX_DEVICES;i++)
{
device_destroy(chr_drv_data.myclass,chr_drv_data.deviceNumber+i);
cdev_del(&chr_drv_data.cd[i].cdev);
}
class_destroy(chr_drv_data.myclass);
unregister_chrdev_region(chr_drv_data.deviceNumber,MAX_DEVICES);
printk("module unloaded\n");
}

module_init(cdriver_init);
module_exit(cdriver_exit);