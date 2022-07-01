obj-m := calculatordriver.o

	KERNELDIR=/lib/modules/$(shell uname -r)/build

	PWD:=$(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc add.c -o add
	gcc sub.c -o sub
	gcc mul.c -o mul
	gcc div.c -o div

install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -rf add mul div sub

