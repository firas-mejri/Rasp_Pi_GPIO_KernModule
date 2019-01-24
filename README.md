#Led Kernel Module

This is a kernel module for a character device that controls leds through Raspberry Pi GPIOs

Compiling: make
Initialising the module: 
	- mknod /dev/led c 60 0
	- chmod 655 /dev/led
	- insmod led.ko
Using the module:
	- as a binary counter : echo "a" > /dev/led
	- as loading led show : cat /dev/led
