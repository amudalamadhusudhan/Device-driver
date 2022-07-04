
obj-m := sem.o

	KERNELDIR=/lib/modules/$(shell uname -r)/build

	PWD:=$(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc write.c -o writeapp1
	gcc writeapp2.c -o writeapp2
	gcc read.c -o readapp

install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -rf readapp writeapp1 writeapp2