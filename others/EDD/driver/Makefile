
	obj-m := driver.o

	KERNELDIR = /lib/modules/$(shell uname -r)/build

	PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o user user.c
	
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -f user
