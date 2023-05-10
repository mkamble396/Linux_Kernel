obj-m += i2c_module_o.o

export KERNEL_ROOT=$(BASE_INSTALL_DIR)/step-3/$(shell uname -r)

modules:
	@$(MAKE) -C$(KERNEL_ROOT) M=$(shell pwd)modules

clean:
	@$(MAKE) -C$(KERNEL_ROOT) M=$(shell pwd)clean


