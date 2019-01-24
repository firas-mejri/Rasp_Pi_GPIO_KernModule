#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/proc_fs.h>
#include <linux/fcntl.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include <linux/delay.h>

#define A1 17
#define A2 18
#define A3 19
#define A4 21

int count_open(struct inode *inode, struct file *filp);
int count_release(struct inode *inode, struct file *filp);
ssize_t count_read(struct file *filp, char *buf, size_t count, loff_t *offp);
ssize_t count_write(struct file *filp, const char *buf, size_t count, loff_t *offp);

int count_init(void);
void count_exit(void);



/*fops*/

struct file_operations count_fops = {
	.owner=THIS_MODULE,
	.read=count_read,
	.write=count_write,
	.open=count_open,
	.release=count_release
};


/* init | exit */

module_init(count_init);
module_exit(count_exit);

/* gloabal vars */

int count_major = 60;
int count_minor = 0;
dev_t dev;


/* implementation init */

int count_init(){

	int result;
	dev = MKDEV(count_major, count_minor);
	result = register_chrdev_region(dev, 1, "counter");
	if(result<0){
	printk(KERN_WARNING,"majeur non dispo");
	return result; 
	}

	printk(KERN_INFO "compteur: initialisation des GPIO gpio...");

	gpio_request(A1, "a1");
	gpio_request(A2, "a2");
	gpio_request(A3, "a3");
	gpio_request(A4, "a4");

	gpio_direction_output(A1, 1);
	gpio_direction_output(A2, 1);
	gpio_direction_output(A3, 1);
	gpio_direction_output(A4, 1);

	return 0;
}


/* implementation exit */

void count_exit(void){

	unregister_chrdev_region(dev, 1);
	/* libération des GPIO */
	gpio_free(A1);
	gpio_free(A2);
	gpio_free(A3);
	gpio_free(A4);
}


int count_open(struct inode *inode, struct file *filp){

	return 0;

}

int count_release(struct inode *inode, struct file *filp){

	return 0;

}


ssize_t count_read(struct file *filp, char *buf, size_t count, loff_t *offp){

	gpio_set_value(A1, 0);
	gpio_set_value(A2, 0);
	gpio_set_value(A3, 0);
	gpio_set_value(A4, 0);
	msleep_interruptible(1500);

	gpio_set_value(A1, 1);
        gpio_set_value(A2, 0);
        gpio_set_value(A3, 0);
        gpio_set_value(A4, 0);
        msleep_interruptible(1500);

	gpio_set_value(A1, 1);
        gpio_set_value(A2, 1);
        gpio_set_value(A3, 0);
        gpio_set_value(A4, 0);
        msleep_interruptible(1500);

	gpio_set_value(A1, 1);
        gpio_set_value(A2, 1);
        gpio_set_value(A3, 1);
        gpio_set_value(A4, 0);
        msleep_interruptible(1500);

	gpio_set_value(A1, 1);
        gpio_set_value(A2, 1);
        gpio_set_value(A3, 1);
        gpio_set_value(A4, 1);

	return 1;

}

ssize_t count_write(struct file *filp, const char *buf, size_t count, loff_t *offp){

	int i = 0;

	gpio_set_value(A1, 0);
        gpio_set_value(A2, 0);
        gpio_set_value(A3, 0);
        gpio_set_value(A4, 0);
        msleep_interruptible(1500);

	while( i < 5 ){
		gpio_set_value(A1, 1);
        	gpio_set_value(A2, 0);
        	gpio_set_value(A3, 0);
        	gpio_set_value(A4, 0);
        	msleep_interruptible(1500);

		gpio_set_value(A1, 0);
                gpio_set_value(A2, 1);
                gpio_set_value(A3, 0);
                gpio_set_value(A4, 0);
                msleep_interruptible(1500);

		gpio_set_value(A1, 1);
                gpio_set_value(A2, 1);
                gpio_set_value(A3, 0);
                gpio_set_value(A4, 0);
                msleep_interruptible(1500);

		gpio_set_value(A1, 0);
                gpio_set_value(A2, 0);
                gpio_set_value(A3, 1);
                gpio_set_value(A4, 0);
                msleep_interruptible(1500);

		gpio_set_value(A1, 1);
                gpio_set_value(A2, 0);
                gpio_set_value(A3, 1);
                gpio_set_value(A4, 0);
                msleep_interruptible(1500);

		gpio_set_value(A1, 0);
                gpio_set_value(A2, 1);
                gpio_set_value(A3, 1);
                gpio_set_value(A4, 0);
                msleep_interruptible(1500);

		gpio_set_value(A1, 1);
                gpio_set_value(A2, 1);
                gpio_set_value(A3, 1);
                gpio_set_value(A4, 0);
                msleep_interruptible(1500);

		gpio_set_value(A1, 0);
                gpio_set_value(A2, 0);
                gpio_set_value(A3, 0);
                gpio_set_value(A4, 1);
                msleep_interruptible(1500);

		gpio_set_value(A1, 1);
                gpio_set_value(A2, 0);
                gpio_set_value(A3, 0);
                gpio_set_value(A4, 1);
                msleep_interruptible(1500);

		gpio_set_value(A1, 0);
                gpio_set_value(A2, 1);
                gpio_set_value(A3, 0);
                gpio_set_value(A4, 1);
                msleep_interruptible(1500);

		gpio_set_value(A1, 1);
                gpio_set_value(A2, 1);
                gpio_set_value(A3, 0);
                gpio_set_value(A4, 1);
                msleep_interruptible(1500);

		gpio_set_value(A1, 0);
                gpio_set_value(A2, 0);
                gpio_set_value(A3, 1);
                gpio_set_value(A4, 1);
                msleep_interruptible(1500);

		gpio_set_value(A1, 1);
                gpio_set_value(A2, 0);
                gpio_set_value(A3, 1);
                gpio_set_value(A4, 1);
                msleep_interruptible(1500);

		gpio_set_value(A1, 0);
                gpio_set_value(A2, 1);
                gpio_set_value(A3, 1);
                gpio_set_value(A4, 1);
                msleep_interruptible(1500);

		gpio_set_value(A1, 1);
                gpio_set_value(A2, 1);
                gpio_set_value(A3, 1);
                gpio_set_value(A4, 1);

		i++;
	}
	return 1;

}






