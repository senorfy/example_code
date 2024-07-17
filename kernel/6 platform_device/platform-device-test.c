#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>

#include <linux/platform_device.h>

#define CDN_DRIVER_NAME "chendening"

static int cdn_probe(struct platform_device *devptr)
{
	printk("chendening cdn_probe success.\n");
	return 0;
}

static int cdn_remove(struct platform_device *devptr)
{
	printk("chendening cdn_remove success.\n");
	return 0;
}


static struct platform_driver cdn_driver = {
	.probe		= cdn_probe,
	.remove		= cdn_remove,
	.driver		= {
		.name	= CDN_DRIVER_NAME,
		.pm	= NULL,
	},
};

static struct platform_device * platfrom_devptr;

int chendening_test_init(void)
{
	int err;
	err = platform_driver_register(&cdn_driver);
	
	platfrom_devptr = platform_device_register_simple(CDN_DRIVER_NAME,
							 0, NULL, 0);

	if (platfrom_devptr != NULL)
	{
		printk("platfrom_devptr ok");
	}

	if (IS_ERR(platfrom_devptr))
	{
		printk("error when creating platfrom device\n");
	}
	
    printk("chendening test success\n");
    return 0;
}

void chendening_test_exit(void)
{
	platform_device_unregister(platfrom_devptr);
	platform_driver_unregister(&cdn_driver);
    printk("chendening test exit\n");
}

module_init(chendening_test_init);
module_exit(chendening_test_exit);
MODULE_DESCRIPTION("chendening");
MODULE_LICENSE("GPL");
