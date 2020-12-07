CC = arm-none-linux-gnueabi-gcc
PWD := $(shell pwd)
KDIR := /root/work/achroimx6q/kernel
APP := project_fire
DD := firesensor_driver
obj-m := $(DD).o

all:	$(DD) $(APP)

$(DD):	$(DD).c
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules ARCH=arm

$(APP):	$(APP).c
	$(CC) -o $(APP) $(APP).c

clean:
	rm -rf *.ko *.mod.* *.order *.symvers *.o $(APP)
