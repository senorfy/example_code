#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>  /* pr_info(() */
#include <linux/delay.h>  /* msleep() */
#include <linux/version.h> /* Linux vresion */

#include <linux/debugfs.h>
#include <linux/fs.h>

#define MAX_BUFFER_SIZE 1024

static char debugfs_buffer[MAX_BUFFER_SIZE];

static ssize_t debugfs_file_read(struct file *file, char __user *buffer, size_t count, loff_t *ppos)
{
    ssize_t ret;

    ret = simple_read_from_buffer(buffer, count, ppos, debugfs_buffer, strlen(debugfs_buffer));
    if (ret < 0)
        return ret;

    return ret;
}

static ssize_t debugfs_file_write(struct file *file, const char __user *buffer, size_t count, loff_t *ppos)
{
    ssize_t ret;

    ret = simple_write_to_buffer(debugfs_buffer, sizeof(debugfs_buffer), ppos, buffer, count);
    if (ret < 0)
        return ret;

    return ret;
}

static const struct file_operations debugfs_file_ops = {
    .read = debugfs_file_read,
    .write = debugfs_file_write,
};

struct dentry* debugfs_dir;

int debugfs_init(void)
{
	struct dentry* debugfs_file;
	debugfs_dir = debugfs_create_dir("chendening", NULL);
	
    if (!debugfs_dir) {
        printk("Failed to create debugfs directory\n");
        return -ENOMEM;
    }

    debugfs_file = debugfs_create_file("debugfs_file", 0644, debugfs_dir, NULL, &debugfs_file_ops);
    if (!debugfs_file) {
        printk("Failed to create debugfs file\n");
        debugfs_remove_recursive(debugfs_dir);
        return -ENOMEM;
    }

    printk("Debugfs example module loaded\n");
	return 0;
}

void debugfs_exit(void)
{
	debugfs_remove_recursive(debugfs_dir);
	printk("chendening test exit\n");
}

module_init(debugfs_init);
module_exit(debugfs_exit);
MODULE_DESCRIPTION("chendening");
MODULE_LICENSE("GPL");