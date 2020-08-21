#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <uapi/asm-generic/errno-base.h>
#include <linux/string.h>

#define DEVICE_NAME "eudyptula"
#define MAX_EUDYPTULA_BUFFER 10

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sebastian Fricke");
MODULE_DESCRIPTION("Eudyptula challenge number 6");
MODULE_VERSION("0.1");

static ssize_t eudyptula_read(struct file *, char __user *, size_t , loff_t *);
static ssize_t eudyptula_write(struct file *, const char __user *, size_t, loff_t *);
static int eudyptula_open(struct inode *, struct file *);
static int eudyptula_release(struct inode *, struct file *);

static char intern_buffer[MAX_EUDYPTULA_BUFFER] = {0};
static char new_buffer[MAX_EUDYPTULA_BUFFER] = {0};

static struct file_operations eudyptula_fops = {
	.owner = THIS_MODULE,
	.read = eudyptula_read,
	.write = eudyptula_write,
	.open = eudyptula_open,
	.release = eudyptula_release
};

static struct miscdevice eudyptula = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &eudyptula_fops
};

static ssize_t eudyptula_read(struct file *fp, char __user *buffer,
				    size_t count , loff_t *offset)
{
	int conversion_bytes = 0;
	long copy_bytes = 0;

	conversion_bytes = scnprintf(intern_buffer, 3, "%d", eudyptula.minor);
	if (conversion_bytes <= 0) {
		pr_warn("%s: Conversion of ID to str failed\n", DEVICE_NAME);
		return -1;
	}

	copy_bytes = copy_to_user(buffer, intern_buffer, conversion_bytes);
	if (copy_bytes < 0) {
		pr_warn("%s: Copy to user failed\n", DEVICE_NAME);
		return -1;
	}
	return copy_bytes;
}

static ssize_t eudyptula_write(struct file *fp, const char __user *buffer,
				     size_t count, loff_t *offset)
{
	int ret = 0;
	if (count > MAX_EUDYPTULA_BUFFER) {
		return -EOVERFLOW;
	}

	// Reset the buffer after each call
	if (strnlen(new_buffer, MAX_EUDYPTULA_BUFFER) > 0) {
		memset(new_buffer, 0, MAX_EUDYPTULA_BUFFER);
	}

	ret = copy_from_user(new_buffer, buffer, count);
	if (ret != 0) {
		return -EFAULT;
	}
	if (strncmp(new_buffer, intern_buffer, 4) != 0) {
		return -EINVAL;
	}
	return ret;
}

static int eudyptula_open(struct inode *inode, struct file *fp)
{
	return 0;
}

static int eudyptula_release(struct inode *inode, struct file *fp)
{
	return 0;
}


static int __init eudyptula_init(void)
{
	return misc_register(&eudyptula);
}

static void __exit eudyptula_exit(void)
{
	return misc_deregister(&eudyptula);
}

module_init(eudyptula_init);
module_exit(eudyptula_exit);
