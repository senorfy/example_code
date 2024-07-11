#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>  /* pr_info(() */
#include <linux/delay.h>  /* msleep() */
#include <linux/version.h> /* Linux vresion */

#include <linux/device.h>

static struct class *test_class;
static struct device dev;


static const struct device_type bt_host = {
	.name    = "host",
};

int class_create_init(void)
{
	test_class = class_create(THIS_MODULE, "chendening");
    printk("module loaded success\n");
	
	dev.type = &bt_host;
	dev.class = test_class;
	
	device_initialize(&dev);/*初始化*/
	
	dev_set_name(&dev, "hfy");
	if (device_add(&dev) < 0) {
		printk("failed to register connection device!!!!\n");
		return -1;
	}

	return 0;
}

void class_create_exit(void)
{
	class_destroy(test_class);
	printk("chendening test exit\n");
}

module_init(class_create_init);
module_exit(class_create_exit);
MODULE_DESCRIPTION("chendening");
MODULE_LICENSE("GPL");