obj-m := cal.o

	KERNELDIR=/lib/modules/$(shell uname -r)/build

	PWD:=$(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc user.c -o user
install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -rf user

