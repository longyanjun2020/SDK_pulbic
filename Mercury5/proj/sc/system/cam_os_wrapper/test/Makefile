obj-m       := linux_ktest.o
linux_ktest-objs := ../src/cam_os_wrapper.o cam_os_wrapper_linux_kernel_test.o

export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabihf-

KERNEL = /home/giggs.huang/eclipse_workspace/linux-3.18
CC  = $(CROSS_COMPILE)gcc
APP = cam_os_wrapper_linux_ktest
EXTRA_CFLAGS := -I/home/giggs.huang/eclipse_workspace/IPCM/openmax/cam_os_wrapper/pub/ -I$(KERNEL)/drivers/mstar/include/

all:
	make modules -C $(KERNEL)  M=`pwd`
	#$(CROSS_COMPILE)strip -g cam_os_wrapper_linux_ktest.ko
	#$(CC) $(APP).c -o $(APP)

clean:
	make modules clean -C $(KERNEL)  M=`pwd`
	rm -rf $(APP)
    
