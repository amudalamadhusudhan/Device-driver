
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/types.h>
#include<linux/cdev.h>
#include<linux/interrupt.h>
#include<linux/gpio.h>
#include<asm/uaccess.h>

#define NAME SRA
#define SUCCESS 1
#define DEBOUNCE_TIME 200
static unsigned int gpioLED = 6;
static unsigned int gpioSwitch = 5;
static bool gpioVal=0;

unsigned long IRQflags = IRQF_TRIGGER_RISING;
static int irqNumber,numberPresses;

MODULE_LICENSE("GPL");
static irq_handler_t myinterrupthandler(unsigned int irq,void *dev_id,struct pt_regs *regs);

//Init module
static int __init prog_init(void)
{
    int result;
    if(!gpio_is_valid(gpioLED))
    {
        printk(KERN_ALERT "\n GPIO_TEST: invalid LED GPIO\n");
        return -ENODEV;
    }
    gpio_request(gpioLED,"GPIO_6");
    gpio_direction_output(gpioLED,1);
    gpio_export(gpioLED,false);

    if(!gpio_is_valid(gpioSwitch))
    {
        printk(KERN_ALERT "\n GPIO_TEST: invalid SWITCH GPIO\n");
        return -ENODEV;
    }
    gpio_request(gpioSwitch,"GPIO_5");
    gpio_direction_input(gpioSwitch);
    gpio_set_debounce(gpioSwitch,DEBOUNCE_TIME);

    //interrupt
    irqNumber=gpio_to_irq(gpioSwitch);

    result=request_irq(irqNumber,
                      (irq_handler_t) myinterrupthandler,
                      IRQflags,
                      "LED-SWITCH HANDLER",
                      NULL);
    
    return 0;

}

//cleanup 
static void __exit prog_exit(void)
{
    free_irq(irqNumber,NULL);
    gpio_unexport(gpioLED);
    gpio_unexport(gpioSwitch);
    printk("\n have unregistered that stuff that allocated...bye dude..\n");
}
static irq_handler_t myinterrupthandler(unsigned int irq,void *dev_id,struct pt_regs *regs)
{
    gpioVal=!gpioVal;
    gpio_set_value(gpioLED,gpioVal);
    numberPresses++;
    printk("\n LED-SWITCH: number of interrupts generated %d\n",numberPresses);
    return (irq_handler_t) IRQ_HANDLED;
}
module_init(prog_init);
module_exit(prog_exit);