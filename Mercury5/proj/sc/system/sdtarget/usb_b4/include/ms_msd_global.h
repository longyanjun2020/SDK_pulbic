#ifndef _MS_MSD_GLOBAL_H_
#define _MS_MSD_GLOBAL_H_
#include "sys_hal_bsp.h"
#include "globalvar.h"
#include "ms_compiler.h"
#include "ms_config.h"
#include "ms_cpu.h"
#include "ms_drc.h"
#include "ms_dma.h"
#include "ms_otg.h"
#include "ms_usb.h"
#include "ms_function.h"
#include "ms_msd_fn_xfer.h"
#include "ms_msd_fn_scsi.h"
#include "bootrom.h"
#include "plfcfg.h"

#ifdef Eable_Usb_Host_Mode
#include "ms_host.h"
#endif

//
//  USB device mode buffer definition
//
#define USB_BUFSIZE SYSNUM_USBDATA_BUFFER_SIZE

#define	SD_LUN		0
#define	NAND_LUN	1

//bits for usb flag
#define USB_CMD_RECEIVED      1
#define USB_TX_FLAG           2
#define USB_INTR_HAPPENED     4

#ifdef CYGHWR_MSTAR_PLATFORM_BIG2
#define GPIOSEL     (MISC+(0x0d*4))                        //gpio interrupt select
#define	GPIO_BASE	0xBF822000
#define	GPIO_OE		(GPIO_BASE+0x11*4)
#define	GPIO_DATA	(GPIO_BASE+0x15*4)
#define	GPIO1_PIN	2
#define MISC    0xbf806000
#define Read_REG16(reg_adr)             ( *( (volatile U16  *) (reg_adr) ) )
#define Write_REG16( _register_, _value_ ) \
        (*((volatile U16 *)(_register_)) = (_value_))
#endif

typedef struct _IntrReg
{
	U8 DmaIntr;
	U8 UsbIntr;
	U16 TxIntr;
	U16 RxIntr;
}UsbIntrReg;

void Init_gUSB_Var(USB_VAR *gUSBStruct, vendorCmdStruct *pCmdStruct);
void otgInitMassBuffer(USB_VAR *gUSBStruct);
void Init_vendorCmd_Var(vendorCmdStruct *pCmdStruct);

#endif   //_MS_MSD_GLOBAL_H_
