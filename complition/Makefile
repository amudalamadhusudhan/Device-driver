obj-m :=comp.o

	KERNELDIR=/lib/modules/$(shell uname -r)/build

	PWD:=$(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc writeapp1.c -o writeapp1
	gcc writeapp2.c -o writeapp2
	gcc readapp.c -o readapp

install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -rf readapp writeapp1 writeapp2

