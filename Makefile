obj-m += led.o

KERNDIR := /lib/modules/$(shell uname -r)/build

default:
	$(MAKE) -C $(KERNDIR) M=$(shell pwd) modules
clean:
	$(MAKE) -C $(KERNDIR) m=$(shell pwd) clean
