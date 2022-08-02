
	obj-m := driver.o

	KERNELDIR = /lib/modules/$(shell uname -r)/build

	PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o r1 r1.c
	gcc -o w1 w1.c
	gcc -o r2 r2.c
	
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -f w1
	rm -f r1
	rm -f r2
