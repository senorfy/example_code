#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>  /* pr_info(() */
#include <linux/delay.h>  /* msleep() */
#include <linux/version.h> /* Linux vresion */

#include <linux/device.h>

static struct class *test_class;

int class_create_init(void)
{
	test_class = class_create(THIS_MODULE, "chendening");
    printk("module loaded success\n");
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