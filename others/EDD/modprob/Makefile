
	obj-m := AVG_MOD/ ADD_MOD/

	KERNELDIR = /lib/modules/$(shell uname -r)/build

	PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

prepare:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_prepare

install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
	depmod -a

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -rf /lib/modules/$(shell uname -r)/extra*
