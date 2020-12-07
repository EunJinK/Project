#include <linux/gpio.h>
#include <linux/uaccess.h>
#include <linux/input.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#define GPIO_DATA IMX_GPIO_NR(2,5)


static int fire_sensor_open(struct inode *inode, struct file *file);
static int fire_sensor_release(struct inode *inode, struct file *file);
static int fire_sensor_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
static int fire_sensor_init(void);
static void fire_sensor_exit(void);
static int fire_sensor_register_cdev(void);

static int fire_major = 0, fire_minor = 0;
static dev_t fire_sensor_dev;
static struct cdev fire_sensor_cdev;


static int fire_sensor_open(struct inode *inode, struct file *file)
{
	printk(KERN_ALERT "< fire_Device has been opened > \n");
	return 0;
}

static int fire_sensor_release(struct inode *inode, struct file *file)
{
	printk(KERN_ALERT "< fire_Device has been closed > \n");
	return 0;
}

static int fire_sensor_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	int res;
	char data[10] = {0};
	res = gpio_get_value(GPIO_DATA);
	sprintf(data,"%d",res);
	res = copy_to_user(buf,&data,count);
	return 0;
}

struct file_operations fire_sensor_fops = {
	.open = fire_sensor_open,
	.release = fire_sensor_release,
	.read = fire_sensor_read,
};

static int fire_sensor_init(void)
{
	int result = 0;
	printk(KERN_ALERT "< fire Sensor Module is up > \n");
	if((result = fire_sensor_register_cdev())<0){
		printk(KERN_ALERT "< fire Sensor Register Fail > \n");
		return result;
	}

	result = gpio_request(GPIO_DATA,"DATA_PIN");
	if(result != 0 ){
		printk(KERN_ALERT "< DATA_PIN Request Fail > \n");
		return -1;
	}
	result = gpio_direction_input(GPIO_DATA);
 	if (result != 0) {
 		printk(KERN_ALERT "< DATA_PIN Configure set Fail > \n");
 		return -1;
	}
	return 0;
}

static void fire_sensor_exit(void)
{
	printk(KERN_ALERT "< fire Sensor Module is down > \n");
	gpio_free(GPIO_DATA);
	cdev_del(&fire_sensor_cdev);
	unregister_chrdev_region(fire_sensor_dev,1);
}

static int fire_sensor_register_cdev(void)
{
	int error;

	if(fire_major)
	{
		fire_sensor_dev = MKDEV(fire_major, fire_minor);
		error = register_chrdev_region(fire_sensor_dev,1, "fire_sensor");
	}
	else
	{
		error = alloc_chrdev_region(&fire_sensor_dev,fire_minor,1, "fire_sensor");
		fire_major = MAJOR(fire_sensor_dev);
	}

	if(error<0)
	{
		printk(KERN_WARNING "fire_sensor : can't get major %d\n", fire_major);
		return -1;
	}

	printk(KERN_ALERT "major number = %d\n", fire_major);
	cdev_init(&fire_sensor_cdev, &fire_sensor_fops);
	fire_sensor_cdev.owner = THIS_MODULE;
	fire_sensor_cdev.ops = &fire_sensor_fops;
	error = cdev_add(&fire_sensor_cdev, fire_sensor_dev,1);

	if(error)
	{
		printk(KERN_NOTICE "fire sensor Register Error %d\n", error);
	}
	return 0;
}

MODULE_AUTHOR("hi");
MODULE_DESCRIPTION("HUINS fire sensor Device Driver");
MODULE_LICENSE("GPL");
module_init(fire_sensor_init);
module_exit(fire_sensor_exit);

