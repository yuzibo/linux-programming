/*************************************************************************
     File Name: yubochar.c
     Author: yubo
     Mail: yuzibode@126.com
     Created Time: 2016年01月17日 星期日 20时02分10秒
references:
http://derekmolloy.ie/writing-a-linux-kernel-module-part-2-a-character-device/
 ************************************************************************/
#include<linux/mutex.h>
#include<linux/err.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/device.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<asm/uaccess.h>
#define DEVICE_NAME "yubochar"
#define CLASS_NAME "yubo-c"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("yu bo");
MODULE_DESCRIPTION("a simple linux char driver for the test");
MODULE_VERSION("0.1");
static int majornumber;
static char message[256] = {0};
static short size_of_message;
static int numberopens = 0;
static struct class* yuboclass = NULL;
static struct device* yubodevice = NULL;
static DEFINE_MUTEX(yubochar_mutex);
/*
 * The prototype functions for character driver
 *
 */
static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *,char *, size_t, loff_t *);
static ssize_t dev_write(struct file *,const char *,size_t, loff_t *);
/*
 * C99 syntax structure.
 */
static struct file_operations fops ={
	.open = dev_open,
	.read = dev_read,
	.write = dev_write,
	.release = dev_release,
};
/*
 * the __init macro means that for a build-in driver
 */
static int __init yubochar_init(void){
	printk(KERN_INFO "yubochar: Initializing the yubochar LKM\n");
	/*
	 * Try to dynamically allocate a major number
	 * @register_chrdev
	 */
	majornumber = register_chrdev(0,DEVICE_NAME, &fops);
	if(majornumber < 0){
		printk(KERN_ALERT "yubochar failed to register a major number\n");
		return majornumber;
	}
	printk(KERN_INFO "yubochar: registered corrently with major number %d\n",majornumber);
	/*
	 * @register the device class
	 */
	yuboclass = class_create(THIS_MODULE,CLASS_NAME);
	if(IS_ERR(yuboclass)){
		unregister_chrdev(majornumber,DEVICE_NAME);
		printk(KERN_ALERT "Failed to register device class\n");
		return PTR_ERR(yuboclass);
	}
	printk(KERN_INFO "yubochar: device class register corrently\n");
	/*
	 *
	 * @REgister the device driver
	 */
	yubodevice = device_create(yuboclass,NULL,MKDEV(majornumber,0),NULL,DEVICE_NAME);
	if(IS_ERR(yubodevice)){ /*Clean up if there is an error*/
		class_destroy(yuboclass);
		unregister_chrdev(majornumber,DEVICE_NAME);
		printk(KERN_ALERT "Failed to create the device\n");
		return PTR_ERR(yubodevice);
	}
	printk(KERN_INFO "yubochar: device class created corrently\n");
	/*
	 * Initialize the mutex lock dynamically
	 */
	mutex_init(&yubochar_mutex);
	return 0;
}
/*
 * The LKM clean up function
 *
 */
static void __exit yubochar_exit(void){
	mutex_destroy(&yubochar_mutex);
	device_destroy(yuboclass,MKDEV(majornumber, 0));
	class_unregister(yuboclass);
	class_destroy(yuboclass);
	unregister_chrdev(majornumber, DEVICE_NAME);
	printk(KERN_INFO "yubochar: Goodbye from the LKM!\n");
}
/*
 * The device open function that is called each time the device is opened
 * This will only increment the numberopens
 */
static int dev_open(struct inode *inodep, struct file *filep){
	if(!mutex_trylock(&yubochar_mutex)){
		printk(KERN_ALERT "yubochar: Device in use by another process");
		return -EBUSY;
	}
	numberopens++;
	printk(KERN_INFO "yubochar: DEVICE has been opened %d times\n",numberopens);
	return 0;
}
/*
 * This function is  called whenever device is being read from user space .data is being sent from the device to the user.In this case is uses the copy_
 *to_user() function to send the buffer string to the user and captures any  * errors
 *@parma filep A pointer to a file object
 *@parma buffer The pointer to the buffer to which this function writes the  *        data
 *@parma len The length of the b
 *@parma offset The offset if required
 */
static ssize_t dev_read(struct file *filep,char *buffer, size_t len, loff_t *offset){
	int error_count = 0;
	/*
	 * copy_to_user has the format(*to, *from, size)
	 */
	error_count = copy_to_user(buffer, message, size_of_message);
	if(error_count == 0){
		printk(KERN_INFO "yubochar: Sent %d characters to the user\n",size_of_message);
		/*clear the position to the start*/
		return (size_of_message);
	}
	else{
		printk(KERN_INFO "yubochar: Failed to send %d characters to the user\n",error_count);
		return -EFAULT;
	}
}
/*
 * This function is called whenever the device is being written to from user * space .data is sent to the devicv from the user.The data is copied to the * message[] array in this .
 * LKM using the sprintg() function along with the length of the string.
 *@parma filep a pointer to a file object
 *@parma buffer The buffer to that contains the string to write to the device
 *@parma len The length of the array of data that is being passed in the const char buffer
 *@parma offset The offset if required
 *
 */
static ssize_t dev_write(struct file *filep,const char *buffer, size_t len, loff_t *offset){
	sprintf(message,"%s(%d letters)",buffer,len);
	size_of_message = strlen(message);
	printk(KERN_INFO "yubochar: Received %d characters from the user\n",len);
	return len;
}
/*
 *
 *
 */
static int dev_release(struct inode *inodep,struct file *filep){
	mutex_unlock(&yubochar_mutex);/*Releases the mutex */
	printk(KERN_INFO "yubochar: Device successfully closed\n");
	return 0;

}
module_init(yubochar_init);
module_exit(yubochar_exit);




/*
 *
 *
 * User Access to the Device using Udev Rules
 *
 */
