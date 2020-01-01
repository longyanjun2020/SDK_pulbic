#
# Makefile for MStar fb device drivers.

MS_ARCH_NAME=infinity3
MS_OS_GOP_NAME=linux

# general options
EXTRA_CFLAGS                +=  -Idrivers/mstar/include
#--------gop--------
EXTRA_CFLAGS                +=  -Idrivers/mstar/driver/hal/infinity/gop/inc
EXTRA_CFLAGS                +=  -Idrivers/mstar/driver/hal/infinity/gop/src
EXTRA_CFLAGS                +=  -Idrivers/mstar/driver/drv/gop/pub
EXTRA_CFLAGS                +=  -Idrivers/mstar/driver/drv/gop/src
EXTRA_CFLAGS                +=  -Idrivers/mstar/driver/drv/gop/pub/$(MS_OS_GOP_NAME)
EXTRA_CFLAGS                +=  -Idrivers/mstar/driver/drv/gop/src/$(MS_OS_GOP_NAME)/fb0/gop
EXTRA_CFLAGS                +=  -Idrivers/mstar/driver/drv/gop/src/$(MS_OS_GOP_NAME)/fb0/inv_color
EXTRA_CFLAGS                +=  -Idrivers/mstar/driver/drv/gop/src/$(MS_OS_GOP_NAME)/fb0
EXTRA_CFLAGS                +=  -Idrivers/mstar/driver/drv/gop/inc/$(MS_OS_GOP_NAME)/fb0
EXTRA_CFLAGS                +=  -Idrivers/mstar/driver/drv/gop/src/$(MS_OS_GOP_NAME)/fb1/gop1
EXTRA_CFLAGS                +=  -Idrivers/mstar/driver/drv/gop/src/$(MS_OS_GOP_NAME)/fb1/inv_color
EXTRA_CFLAGS                +=  -Idrivers/mstar/driver/drv/gop/src/$(MS_OS_GOP_NAME)/fb1
EXTRA_CFLAGS                +=  -Idrivers/mstar/driver/drv/gop/inc/$(MS_OS_GOP_NAME)/fb1
EXTRA_CFLAGS                +=  -Idrivers/mstar/driver/drv/gop/src/$(MS_OS_GOP_NAME)/fb2/gop2
EXTRA_CFLAGS                +=  -Idrivers/mstar/driver/drv/gop/src/$(MS_OS_GOP_NAME)/fb2/inv_color
EXTRA_CFLAGS                +=  -Idrivers/mstar/driver/drv/gop/src/$(MS_OS_GOP_NAME)/fb2
EXTRA_CFLAGS                +=  -Idrivers/mstar/driver/drv/gop/inc/$(MS_OS_GOP_NAME)/fb2

EXTRA_CFLAGS      +=  -DGOPOS_TYPE_LINUX_KERNEL

# files
#obj-$(CONFIG_MS_FB_INFINITY)   += gop/mdrv_gop_io.o
#obj-$(CONFIG_MS_FB_INFINITY)   += gop/mdrv_gop.o
#obj-$(CONFIG_MS_FB_INFINITY)   += mdrv_fb.o

obj-$(CONFIG_MS_FB_INFINITY3)   += infinity_gop.o

infinity_gop-objs := ../../hal/infinity/gop/src/hal_gop.o \
                src/drv_gop.o

obj-$(CONFIG_MS_FB_INFINITY3)   += infinity_fb.o

infinity_fb-objs := src/$(MS_OS_GOP_NAME)/fb0/mdrv_fb.o \
                src/$(MS_OS_GOP_NAME)/fb0/inv_color/mdrv_gop0_inv_color.o

obj-$(CONFIG_MS_FB1_INFINITY3)   += infinity_fb1.o

infinity_fb1-objs := src/$(MS_OS_GOP_NAME)/fb1/mdrv_fb1.o \
                src/$(MS_OS_GOP_NAME)/fb1/inv_color/mdrv_gop1_inv_color.o

obj-$(CONFIG_MS_FB2_INFINITY3)   += infinity_fb2.o

infinity_fb2-objs := src/$(MS_OS_GOP_NAME)/fb2/mdrv_fb2.o \
                src/$(MS_OS_GOP_NAME)/fb2/inv_color/mdrv_gop2_inv_color.o