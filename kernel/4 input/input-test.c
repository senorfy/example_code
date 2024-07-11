#include <linux/module.h>
#include <linux/poll.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/major.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/tty.h>
#include <linux/kmod.h>
#include <linux/gfp.h>
#include <linux/gpio/consumer.h>
#include <linux/platform_device.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/slab.h>
#include <linux/fcntl.h>
#include <linux/timer.h>
#include <linux/input.h>
/* https://blog.csdn.net/lihuan680680/article/details/121325980 by 面朝大海0902*/
struct gpio_key{
    int gpio;
    struct gpio_desc *gpiod;
    int flag;
    int irq;
};

struct input_dev *key_input;
static struct gpio_key *ptr_gpio_key;
struct timer_list key_timer;

void timer_function(unsigned long arg)
{
    int value;
    printk(KERN_INFO "%s %s line is %d \r\n", __FILE__, __FUNCTION__, __LINE__);
    struct gpio_key *ptr_gpio_key_temp = arg;
    
    if(ptr_gpio_key_temp == NULL)
        return;
    
    value = gpiod_get_value(ptr_gpio_key_temp->gpiod);

    if(value == 0)
    {
        if(ptr_gpio_key_temp->gpio == ptr_gpio_key[0].gpio)
        {
            input_report_key(key_input, KEY_L, 1);
        }
        else
        {
            input_report_key(key_input, KEY_S, 1);
        }
    }
    else
    {
        if(ptr_gpio_key_temp->gpio == ptr_gpio_key[0].gpio)
        {
            input_report_key(key_input, KEY_L, 0);
        }
        else
        {
            input_report_key(key_input, KEY_S, 0);
        }
    }
    input_sync(key_input);
}

static irqreturn_t gpio_key_isr(int irq, void *dev_id)
{
    key_timer.data =(unsigned long) dev_id;
    mod_timer(&key_timer, jiffies + HZ/4);
    printk(KERN_INFO "%s %s line is %d \r\n", __FILE__, __FUNCTION__, __LINE__);
    return IRQ_HANDLED;
}

static int key_probe(struct platform_device *pdev)
{
    int count = 0;
    int i=0;
    enum of_gpio_flags flag;
    struct device_node *node = pdev->dev.of_node;
    
    printk(KERN_INFO "%s %s line is %d \r\n", __FILE__, __FUNCTION__, __LINE__);
    count = of_gpio_count(node);
    ptr_gpio_key = kzalloc(sizeof(struct gpio_key)*count, GFP_KERNEL);
    
    for(i=0;i<count;i++)
    {
        ptr_gpio_key[i].gpio = of_get_gpio_flags(node, i, &flag);
        if(ptr_gpio_key[i].gpio < 0)
        {
            printk(KERN_ERR "of_get_gpio_flags is err\r\n");
        }
        else
        {
            printk(KERN_INFO "gpio num is %d\r\n",ptr_gpio_key[i].gpio);
        }
        ptr_gpio_key[i].gpiod = gpio_to_desc(ptr_gpio_key[i].gpio);
        ptr_gpio_key[i].flag = flag & OF_GPIO_ACTIVE_LOW;
        ptr_gpio_key[i].irq = gpio_to_irq(ptr_gpio_key[i].gpio);
        request_irq(ptr_gpio_key[i].irq, gpio_key_isr, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, "gpio_key", &ptr_gpio_key[i]);
    }

    /* 1、申请 input_dev */
    key_input = input_allocate_device();
    key_input->name = "key_input";
    
    /* 2、初始化 input_dev，设置产生哪些事件 */
    __set_bit(EV_KEY, key_input->evbit);
    __set_bit(EV_REP, key_input->evbit);

    /* 3、初始化 input_dev，设置产生哪些按键 */
    __set_bit(KEY_L, key_input->keybit);
    __set_bit(KEY_S, key_input->keybit);

    /* 4、注册输入设备 */
    input_register_device(key_input);
    
    init_timer(&key_timer);
    key_timer.function = timer_function;
    key_timer.expires = ~0;
    //add_timer(&key_timer);

    return 0;    
}



static int key_remove(struct platform_device *pdev)
{
    int count = 0;
    int i = 0;
    struct device_node *node = pdev->dev.of_node;

    printk(KERN_INFO "%s %s line is %d \r\n", __FILE__, __FUNCTION__, __LINE__);
    count = of_gpio_count(node);

    for(i=0;i<count;i++)
    {
        free_irq(ptr_gpio_key[i].irq, &ptr_gpio_key[i]);
    }

    kfree(ptr_gpio_key);
    del_timer(&key_timer);

    /* 释放 input_dev */
    input_unregister_device(key_input);
    input_free_device(key_input);

    return 0;    
}


static const struct of_device_id my_key[] =
{
    {.compatible = "my,key_driver"},
    {},
};


static struct platform_driver key_driver =
{
    .probe  = key_probe,
    .remove = key_remove,
    .driver = 
    {
        .name = "key_gpio",
        .of_match_table = my_key,
    },
};


static int __init my_key_init(void)
{
    int result;
    printk(KERN_INFO "%s %s line is %d \r\n", __FILE__, __FUNCTION__, __LINE__);
    result = platform_driver_register(&key_driver);
    return result;
}


static void __exit my_key_exit(void)
{
    printk(KERN_INFO "%s %s line is %d \r\n", __FILE__, __FUNCTION__, __LINE__);
    platform_driver_unregister(&key_driver);
}

module_init(my_key_init);
module_exit(my_key_exit);
MODULE_LICENSE("GPL");
