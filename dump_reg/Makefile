 obj-m := dumreg.o   
 #CROSS_COMPILE=/home/root_work/am335x_4220_tmp/mimi_am335x_4220_v2/cross_compiler/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf- 
 CROSS_COMPILE=/home/AUTO/power/toolchains/gcc-linaro-aarch64-linux-gnu-4.9-2014.09_linux/bin/aarch64-linux-gnu-

ARCH=arm64
    
 #KERNEL_DIR := /lib/modules/3.13.0-24-generic/build/  
 #KERNEL_DIR := /home/AUTO/yanmanjun/xen_on_arm/linux-3.18.14/
 #KERNEL_DIR := /home/AUTO/yanmanjun/working/exynos8890_v1/exynos/
 KERNEL_DIR := /home/AUTO/yanmanjun/working/mkt_8890/e8890_linux_platform_20170308_doing/meta-exynos8890/recipes-kernel/kernel/
 PWD := $(shell pwd)   
      
default:   
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNEL_DIR) M=$(PWD) modules   
    
clean:   
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean   
	-rm *~ 
  

