#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>

#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/poll.h>

static int cdn_char_open(struct inode *inode, struct file *file)
{
	return 0;
}

static int cdn_char_release(struct inode *inode, struct file *file)
{
	return 0;
}

static ssize_t cdn_char_read(struct file *file, char __user *buffer,
				size_t count, loff_t *ppos)
{
	return 0;
}

static ssize_t cdn_char_write(struct file *file, const char __user *buffer,
				size_t count, loff_t *ppos)
{
	return 0;
}

static unsigned int cdn_char_poll(struct file *file, struct poll_table_struct *wait)
{
	return -EOPNOTSUPP;
}

static const struct file_operations cdn_fops = {
	.owner		= THIS_MODULE,
	.open		= cdn_char_open,
	.release	= cdn_char_release,
	.read		= cdn_char_read,
	.write		= cdn_char_write,
	.poll		= cdn_char_poll,
	.llseek		= no_llseek,
};

#define CDN_NAME "chendening"

static struct miscdevice cdn_misc = {
	.fops		= &cdn_fops,
	.minor		= MISC_DYNAMIC_MINOR,	/*自动分配*/
	.name		= CDN_NAME,
};

int chendening_test_init(void)
{
	misc_register(&cdn_misc);
    printk("chendening test success\n");
    return 0;
}

void chendening_test_exit(void)
{
	misc_deregister(&cdn_misc);
    printk("chendening test exit\n");
}

module_init(chendening_test_init);
module_exit(chendening_test_exit);
MODULE_DESCRIPTION("chendening");
MODULE_LICENSE("GPL");
