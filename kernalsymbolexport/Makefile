obj-m:=module2.o export.o

	KERNELDIR=/lib/modules/$(shell uname -r)/build

	PWD:=$(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
	depmod -a
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

