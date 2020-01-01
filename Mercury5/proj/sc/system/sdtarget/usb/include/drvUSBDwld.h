///////////////////////////////////////////////////////////////////////////////////////////////////
// @file   drvUSBDwld.h
// @author MStar Semiconductor Inc.
// @brief  Initial download code from USB
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DRV_USBDWLD_H
#define _DRV_USBDWLD_H

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "globalvar.h"


//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
#define BB_DATA_READY       0x0000
#define BB_DATA_END         0x0001
#define BB_DATA_EMPTY       0x0002

#ifdef CYGHWR_MSTAR_PLATFORM_BIG2
#define REG_MISC_SPARE      0xBF800078
#define REG_SHAREMEM_SRC    0xBF80601C
#endif

#define Bit_Inverse_Clk     0x02
#define Bit_USB_ShareMem    0x02

#define SELECT_NONE         0x00
#define SELECT_ROM          0x01
#define SELECT_RAM          0x02

/* Vendor specific command byte, cmd_bytes[1], for SCSI_VENDOR_XROM, 0xE8 */
#define XROM_USB_UPLOAD_FIXEDLEN    0x00
#define XROM_USB_DOWNLOAD_KEEP      0x01
#define XROM_USB_UPLOAD_SIZE        0x02
#define XROM_USB_ERR_CODE           0x03
#define XROM_USB_DOWNLOAD_END       0x04
#define XROM_USB_SEL_ROMRAM         0x05
#define XROM_USB_UPLOAD_VARLEN      0x06

#if 0
//-------------------------------------------------------------------------------------------------
// Extern Variables
//-------------------------------------------------------------------------------------------------
extern  USB_VAR         usbDrvVar;


//-------------------------------------------------------------------------------------------------
// Function Prototypes
//-------------------------------------------------------------------------------------------------
void    MDrv_USB_NandUplink(void);
void    MDrv_USB_Init(void);
void    MDrv_USB_Stop(void);
S32     MDrv_USB_Write(U8 *buf, U32 len);
S32     MDrv_USB_Read(U8 *buf, U32 len);
void    MDrv_USB_Config(U8 *buf);
void    MDrv_USB_CmdLoop(void *pUsbStruct);
#endif

#endif  // _DRV_USBDWLD_H
