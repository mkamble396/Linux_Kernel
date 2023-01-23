#obj-m := my_intr.o 
obj-m += My_mouse_intr.o 
all:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules
clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean




