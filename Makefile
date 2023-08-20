obj-m += watchpoint_module.o

# Path to the running kernel source
KDIR := /lib/modules/$(shell uname -r)/build

# Specify flags for the module compilation.
EXTRA_CFLAGS=-I$(PWD)/modules/module_param -I$(PWD)/modules/sysfs

# 'make' command will invoke the following:
# 'make -C /lib/modules/$(uname -r)/build M=$(PWD) modules'
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
